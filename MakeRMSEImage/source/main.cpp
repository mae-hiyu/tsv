//
//  main.cpp
//  ImageComparator_MT2
//
//  Created by 渡部 心 on 12/10/15.
//  Copyright (c) 2012年 Shin Watanabe. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <fstream>
#include "fileSystem.hpp"
#include "WorkPile.hpp"
#include "pseudo-color.hpp"
#include <vector>
#include "manipulatePNG.hpp"
#include "manipulateSPI.hpp"
#include <cstdarg>
#include <cmath>

using namespace std;


class CriticalOperation {
    static boost::mutex printfMutex;
    static boost::mutex scanfMutex;
public:
    static void printf(const char* format, ...);
    static void scanf(const char* format, ...);
};

void CriticalOperation::printf(const char* format, ...) {
    boost::mutex::scoped_lock(printfMutex);
    va_list list;
    va_start(list, format);
    vprintf(format, list);
    va_end(list);
}

void CriticalOperation::scanf(const char* format, ...) {
    boost::mutex::scoped_lock(scanfMutex);
    va_list list;
    va_start(list, format);
    vscanf(format, list);
    va_end(list);
}

typedef struct {
    std::vector<double> cAvg;
    std::vector<double> variance;
    std::vector<double> RMSE;
} ImageStatistics;

struct PNGCompareTaskData : public TaskData {
    int fileNumber;
    std::vector<ImageStatistics>* statistics;
    string filename;
    const int refWidth, refHeight;
    unsigned char** refData;
    const int pX, pY, rW, rH;
    PNGCompareTaskData(int taskType, int fileNumber_, std::vector<ImageStatistics>* stats, string filename_,
                       int refWidth_, int refHeight_, unsigned char** refData_,
                       int pX_ = -1, int pY_ = -1, int rW_ = 1, int rH_ = 1) :
    TaskData(taskType), fileNumber(fileNumber_), statistics(stats), filename(filename_),
    refWidth(refWidth_), refHeight(refHeight_), refData(refData_), pX(pX_), pY(pY_), rW(rW_), rH(rH_)
    { };
};

struct SPICompareTaskData : public TaskData {
    int fileNumber;
    std::vector<ImageStatistics>* statistics;
    string filename;
    const SPIHeader &refInfo;
    float*** refData;
    const int pX, pY, rW, rH;
    SPICompareTaskData(int taskType, int fileNumber_, std::vector<ImageStatistics>* stats, string filename_,
                       const SPIHeader &refInfo_, float*** refData_,
                       int pX_ = -1, int pY_ = -1, int rW_ = 1, int rH_ = 1) :
    TaskData(taskType), fileNumber(fileNumber_), statistics(stats), filename(filename_),
    refInfo(refInfo_), refData(refData_),
    pX(pX_), pY(pY_), rW(rW_), rH(rH_)
    { };
};

class ImageCompareWorker : public Worker {
public:
    ImageCompareWorker(int number, TaskBag* taskBag) : Worker(number, taskBag) { };
    //for RMSEImage
    int image_index=0;
    
    void job() {
        switch (_task->tag) {
            case 1:
            {
                PNGCompareTaskData &taskData = (PNGCompareTaskData&)*_task;
                ImageStatistics &statistics = (ImageStatistics&)((*taskData.statistics)[taskData.fileNumber]);
                CriticalOperation::printf("Process %s : %d\n", taskData.filename.c_str(), taskData.fileNumber);
                
                unsigned char** data = NULL;
                int width, height;
                //画像サイズが異なる場合にスキップ．
//                readPNGInfo(taskData.filename.c_str(), &header);
//                if (header.width != taskData.refInfo.width || header.height != taskData.refInfo.height) {
//                    statistics.RMSE.push_back(0.0f);
//                    return;
//                }
                
                ReadPNGFile(taskData.filename.c_str(), &data, &width, &height);
                
                double diffsum[3] = {0.0f, 0.0f, 0.0f};
                double diffrowsum[3] = {0.0f, 0.0f, 0.0f};
                double diff[3] = {0.0f, 0.0f, 0.0f};
                double c1[3] = {0.0f, 0.0f, 0.0f};
                double c2[3] = {0.0f, 0.0f, 0.0f};
                double RGBtoXYZMatrix[9] = {0.4124564, 0.3575761, 0.1804375,
                                            0.2126729, 0.7151522, 0.0721750,
                                            0.0193339, 0.1191920, 0.9503041};
                double diffsumRGB;
                double diffMax = 0;
                std::size_t diffIndex;
                PseudoColor pc;

                //create Pseudo-ColorRMSEImage
                unsigned char **RMSEImage;
                const double RMSEImage_width = width;
                const double RMSEImage_height = height;
                RMSEImage = (png_bytepp)malloc(RMSEImage_height * sizeof(png_bytep));
                for (std::size_t i = 0; i < RMSEImage_height; ++i)
                RMSEImage[i] = (png_bytep)malloc(3*RMSEImage_width * sizeof(png_byte));


                for (int i = 0; i < height; ++i) {
                    if (taskData.pY != -1) {
                        if (i < taskData.pY || i > taskData.pY + taskData.rH - 1) continue;
                    }
                    diffrowsum[0] = diffrowsum[1] = diffrowsum[2] = 0.0;
                    for (int j = 0; j < width; ++j) {
                        if (taskData.pX != -1) {
                            if (j < taskData.pX || j > taskData.pX + taskData.rW - 1) continue;
                        }
                        c1[0] = double(data[i][3 * j + 0]);
                        c1[1] = double(data[i][3 * j + 1]);
                        c1[2] = double(data[i][3 * j + 2]);

                        c2[0] = double(taskData.refData[i][3 * j + 0]);
                        c2[1] = double(taskData.refData[i][3 * j + 1]);
                        c2[2] = double(taskData.refData[i][3 * j + 2]);
                        
                        // transform RGB to XYZ
                        c1[0] = RGBtoXYZMatrix[0] * c1[0] + RGBtoXYZMatrix[1] * c1[1] + RGBtoXYZMatrix[2] * c1[2];
                        c1[1] = RGBtoXYZMatrix[3] * c1[0] + RGBtoXYZMatrix[4] * c1[1] + RGBtoXYZMatrix[5] * c1[2];
                        c1[2] = RGBtoXYZMatrix[6] * c1[0] + RGBtoXYZMatrix[7] * c1[1] + RGBtoXYZMatrix[8] * c1[2];

                        c2[0] = RGBtoXYZMatrix[0] * c2[0] + RGBtoXYZMatrix[1] * c2[1] + RGBtoXYZMatrix[2] * c2[2];
                        c2[1] = RGBtoXYZMatrix[3] * c2[0] + RGBtoXYZMatrix[4] * c2[1] + RGBtoXYZMatrix[5] * c2[2];
                        c2[2] = RGBtoXYZMatrix[6] * c2[0] + RGBtoXYZMatrix[7] * c2[1] + RGBtoXYZMatrix[8] * c2[2];

                        diff[0] = (c1[0] - c2[0]);
                        diff[1] = (c1[1] - c2[1]);
                        diff[2] = (c1[2] - c2[2]);
//                        //相対誤差
//                        diff[0] *= c2[0] == 0 ? 0 : 1.0f / c2[0];
//                        diff[1] *= c2[1] == 0 ? 0 : 1.0f / c2[1];
//                        diff[2] *= c2[2] == 0 ? 0 : 1.0f / c2[2];
                        
                        diffrowsum[0] += diff[0] * diff[0];
                        diffrowsum[1] += diff[1] * diff[1];
                        diffrowsum[2] += diff[2] * diff[2];
                        diffsumRGB =  diff[0] * diff[0] + diff[1]*diff[1] + diff[2]*diff[2];
                        if (diffMax < diffsumRGB)
                            diffMax = diffsumRGB;
                    }
                    diffsum[0] += diffrowsum[0];
                    diffsum[1] += diffrowsum[1];
                    diffsum[2] += diffrowsum[2];
                }

                //create RMSEImage
                std::cout << sqrt(diffMax / 3) << std::endl;
                diffMax =15;
                diffMax = diffMax * diffMax * 3;
                for (std::size_t i = 0; i < RMSEImage_height; ++i)
                {
                    for (std::size_t j = 0; j < RMSEImage_width*3; j+=3)
                    {
                        c1[0] = double(data[i][3 * j/3 + 0]);
                        c1[1] = double(data[i][3 * j/3 + 1]);
                        c1[2] = double(data[i][3 * j/3 + 2]);

                        c2[0] = double(taskData.refData[i][3 * j/3 + 0]);
                        c2[1] = double(taskData.refData[i][3 * j/3 + 1]);
                        c2[2] = double(taskData.refData[i][3 * j/3 + 2]);
                        
                        // transform RGB to XYZ
                        c1[0] = RGBtoXYZMatrix[0] * c1[0] + RGBtoXYZMatrix[1] * c1[1] + RGBtoXYZMatrix[2] * c1[2];
                        c1[1] = RGBtoXYZMatrix[3] * c1[0] + RGBtoXYZMatrix[4] * c1[1] + RGBtoXYZMatrix[5] * c1[2];
                        c1[2] = RGBtoXYZMatrix[6] * c1[0] + RGBtoXYZMatrix[7] * c1[1] + RGBtoXYZMatrix[8] * c1[2];

                        c2[0] = RGBtoXYZMatrix[0] * c2[0] + RGBtoXYZMatrix[1] * c2[1] + RGBtoXYZMatrix[2] * c2[2];
                        c2[1] = RGBtoXYZMatrix[3] * c2[0] + RGBtoXYZMatrix[4] * c2[1] + RGBtoXYZMatrix[5] * c2[2];
                        c2[2] = RGBtoXYZMatrix[6] * c2[0] + RGBtoXYZMatrix[7] * c2[1] + RGBtoXYZMatrix[8] * c2[2];

                        diff[0] = (c1[0] - c2[0]);
                        diff[1] = (c1[1] - c2[1]);
                        diff[2] = (c1[2] - c2[2]);
                        diffsumRGB =  diff[0] * diff[0] + diff[1]*diff[1] + diff[2]*diff[2];

                        diffIndex = (double)(diffsumRGB / diffMax) * 255;
                        if (diffIndex > 255)
                        {
                            diffIndex = 255;
                        }
                        RMSEImage[i][j] = (unsigned char)std::get<0>(pc.getColor(diffIndex));
                        RMSEImage[i][j+1] = (unsigned char)std::get<1>(pc.getColor(diffIndex));
                        RMSEImage[i][j+2] = (unsigned char)std::get<2>(pc.getColor(diffIndex));
                    }
                }
                image_index++;
                writePNGwithDate("pseudo-colorRMSE", image_index, RMSEImage , RMSEImage_width, RMSEImage_height);
                std::cout << image_index << std::endl;
                for (std::size_t j = 0; j < RMSEImage_height; j++) 
                    free(RMSEImage[j]);
                free(RMSEImage);

                double coeff;
                if (taskData.pX != -1 && taskData.pY != -1) {
                    coeff = 1 / double(taskData.rW * taskData.rH);
                }
                else {
                    coeff = 1 / double(taskData.refWidth * taskData.refHeight);
                }
                statistics.RMSE.push_back(sqrt(diffsum[0] * coeff));
                statistics.RMSE.push_back(sqrt(diffsum[1] * coeff));
                statistics.RMSE.push_back(sqrt(diffsum[2] * coeff));
                statistics.RMSE.push_back(sqrt((diffsum[0] + diffsum[1] + diffsum[2]) * coeff / 3));
                
                for (int i = 0; i < height; ++i) {
                    free(data[i]);
                }
                free(data);
            }
                break;
            case 2:
            {
                SPICompareTaskData &taskData = (SPICompareTaskData&)*_task;
                ImageStatistics &statistics = (ImageStatistics&)((*(taskData.statistics))[taskData.fileNumber]);
                CriticalOperation::printf("Process %s : %d\n", taskData.filename.c_str(), taskData.fileNumber);
                
                float*** data;
                int width, height;
                int numWL;
                float minWL, maxWL;
                SPIHeader header;
                readSPIInfo(taskData.filename.c_str(), &header);
                if (header.width != taskData.refInfo.width || header.height != taskData.refInfo.height ||
                    header.numWL != taskData.refInfo.numWL || header.minWL != taskData.refInfo.minWL ||
                    header.maxWL != taskData.refInfo.maxWL) {
                    statistics.RMSE.push_back(0.0f);
                    return;
                }
                
                readSPI(taskData.filename.c_str(), &data, &width, &height, &numWL, &minWL, &maxWL);
                
                std::vector<double> diffsum(numWL, 0.0f);
                std::vector<double> diffrowsum(numWL, 0.0f);
                std::vector<double> diff(numWL, 0.0f);
                std::vector<double> c1(numWL, 0.0f);
                std::vector<double> c2(numWL, 0.0f);
                for (int i = 0; i < height; ++i) {
                    if (taskData.pY != -1) {
                        if (i < taskData.pY || i > taskData.pY + taskData.rH - 1) continue;
                    }
                    for (int j = 0; j < numWL; ++j) {
                        diffrowsum[j] = 0.0f;
                    }
                    for (int j = 0; j < width; ++j) {
                        if (taskData.pX != -1) {
                            if (j < taskData.pX || j > taskData.pX + taskData.rW - 1) continue;
                        }
                        for (int k = 0; k < numWL; ++k) {
                            c1[k] = double(data[i][j][k]);
                            c2[k] = double(taskData.refData[i][j][k]);
                            
                            diff[k] = c1[k] - c2[k];
                            
//                            //相対誤差の算出．
//                            if (c2[k] == 0.0f)
//                                diff[k] = 0.0f;
//                            else
//                                diff[k] /= c2[k];
                            
//                            if (abs(diff[k]) > 100) {
//                                CriticalOperation::printf("%d: big: %d, %d\n", taskData.fileNumber, j, i);
//                                diff[k] = 0.0f;
//                            }
                            diffrowsum[k] += diff[k] * diff[k];
                        }
                    }
                    for (int j = 0; j < numWL; ++j) {
                        diffsum[j] += diffrowsum[j];
                    }
                }
                
                double coeff;
                if (taskData.pX != -1 && taskData.pY != -1) {
                    coeff = 1 / double(taskData.rW * taskData.rH);
                }
                else {
                    coeff = 1 / double(taskData.refInfo.width * taskData.refInfo.height);
                }
                double totalRMSE = 0.0;
                for (int i = 0; i < numWL; ++i) {
                    statistics.RMSE.push_back(sqrt(diffsum[i] * coeff));
                    totalRMSE += diffsum[i];
                }
                statistics.RMSE.push_back(sqrt(totalRMSE * coeff / numWL));
                
                for (int i = 0; i < height; ++i) {
                    for (int j = 0; j < width; ++j) {
                        free(data[i][j]);
                    }
                    free(data[i]);
                }
                free(data);
            }
                break;
            default:
                break;
        }
    };
};

int main(int argc, const char * argv[])
{
    // printf("%ld", sizeof(SPIHeader));
    printf("\n");
//    FileSystem::enumerateFileNames("/Users/Shin");
//    
    if (argc < 4) {
        return -1;
    }
    
    if (!strcmp(argv[1], "b")) {
        
    }
    else if(!strcmp(argv[1], "t")) {
        int pX = -1, pY = -1;
        int rW = 1, rH = 1;
        switch (argc) {
            case 4:
                break;
            case 5:
                return -1;
            case 6:
                pX = atoi(argv[4]);
                pY = atoi(argv[5]);
                break;
            case 7:
                return -1;
            case 8:
                pX = atoi(argv[4]);
                pY = atoi(argv[5]);
                rW = atoi(argv[6]);
                rH = atoi(argv[7]);
                break;
            default:
                break;
        }
        
        const char* ext[] = {".png", ".spi"};
        int whichExt = 0;
        vector<ImageStatistics> stats;
        
        string refName = argv[3];
        string refExt = string(argv[3]).substr(refName.rfind("."));
        for (int i = 0; i < 2; ++i) {
            if (refExt == ext[i]) {
                whichExt = i;
                break;
            }
        }
        
        switch (whichExt) {
            case 0:
            {
                unsigned char** refData = NULL;
                int refWidth, refHeight;
                ReadPNGFile(argv[3], &refData, &refWidth, &refHeight);
                
                string* files;
                int numFiles;
                FileSystem::getFileNames(&files, &numFiles, argv[2], ext[whichExt]);
                stats.resize(numFiles);
                for (int i = 0; i < numFiles; ++i) {
                    printf("%s, ", files[i].c_str());
                }
                printf("\n");
                
                PNGCompareTaskData* ic_tasks = (PNGCompareTaskData*)malloc(numFiles * sizeof(PNGCompareTaskData));
                for (int i = 0; i < numFiles; ++i) {
                    new (&(ic_tasks[i])) PNGCompareTaskData(1, i, &stats, string(argv[2]) + "/" + files[i],
                                                            refWidth, refHeight, refData, pX, pY, rW, rH);
                }
                {
                    WorkPileManager<ImageCompareWorker> mng(boost::thread::hardware_concurrency());
                    for (int i = 0; i < numFiles; ++i) {
                        mng.pushTask(&(ic_tasks[i]));
                    }
                    
                    mng.finish();
                }
                free(ic_tasks);
                
                for (int i = 0; i < refHeight; ++i) {
                    free(refData[i]);
                }
                free(refData);
                
                printf("%dx%d, ", refWidth, refHeight);
                if (pX != -1 && pY != -1) {
                    printf("From [%d, %d] To [%d, %d], ", pX, pY, pX + rW - 1, pY + rH - 1);
                }
                printf("%s\n", argv[2]);
                for (int i = 0; i < stats.size(); ++i) {
                    printf("");
                    printf("%10.6f\n", stats[i].RMSE[3]);
                }
            }
                break;
            case 1:
            {
                float*** refData;
                int refWidth, refHeight;
                int refNumWL;
                float refMinWL, refMaxWL;
                readSPI(argv[3], &refData, &refWidth, &refHeight, &refNumWL, &refMinWL, &refMaxWL);
                SPIHeader refInfo = SPIHeader(refWidth, refHeight, refNumWL, refMinWL, refMaxWL);
                
                string* files;
                int numFiles;
                FileSystem::getFileNames(&files, &numFiles, argv[2], ext[whichExt]);
                stats.resize(numFiles);
                for (int i = 0; i < numFiles; ++i) {
                    printf("%s, ", files[i].c_str());
                }
                printf("\n");
                
                SPICompareTaskData* ic_tasks = (SPICompareTaskData*)malloc(numFiles * sizeof(SPICompareTaskData));
                for (int i = 0; i < numFiles; ++i) {
                    new (&(ic_tasks[i])) SPICompareTaskData(2, i, &stats, string(argv[2]) + "/" + files[i],
                                                            refInfo, refData, pX, pY);
                }
                {
                    WorkPileManager<ImageCompareWorker> mng(boost::thread::hardware_concurrency());
                    for (int i = 0; i < numFiles; ++i) {
                        mng.pushTask(&(ic_tasks[i]));
                    }
                    
                    mng.finish();
                }
                free(ic_tasks);
                
                for (int i = 0; i < refHeight; ++i) {
                    for (int j = 0; j < refWidth; ++j) {
                        free(refData[i][j]);
                    }
                    free(refData[i]);
                }
                free(refData);
                
                printf("%dx%d, ", refWidth, refHeight);
                if (pX != -1 && pY != -1) {
                    printf("From [%d, %d] To [%d, %d], ", pX, pY, pX + rW - 1, pY + rH - 1);
                }
                printf("%s\n", argv[2]);
                for (int j = 0; j < refNumWL; ++j) {
                    printf("%12g, ", refMinWL + (refMaxWL - refMinWL) / (refNumWL - 1) * j);
                }
                printf("       total\n");
                for (int i = 0; i < stats.size(); ++i) {
                    for (int j = 0; j < refNumWL; ++j) {
                        printf("%12g, ", stats[i].RMSE[j]);
                    }
                    printf("%12g\n", stats[i].RMSE[refNumWL]);
                }
            }
                break;
            default:
                break;
        }
    }
    
    return 0;
}

