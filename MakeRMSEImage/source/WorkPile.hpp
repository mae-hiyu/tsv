//
//  WorkPile.hpp
//  GIRenderer
//
//  Created by 渡部心 on 12/02/10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef GIRenderer_WorkPile_hpp
#define GIRenderer_WorkPile_hpp

#include <cstdlib>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>

struct TaskData {
    int tag;
    TaskData(int tag_) : tag(tag_) { };
};

//タスクバッグ。タスクを求めてきたワーカーにタスクを渡す。
//タスクを渡す際は同じものを複数スレッドに渡さないよう、排他制御。
class TaskBag {
    boost::mutex _mtx;
    std::vector<TaskData*> _tasks;
public:
    void pushTask(TaskData* task);
    bool getTasks(TaskData** task);
    int numTasks();
};

//ワーカー。マネージャーが作成したスレッドでrun()を実行。
//タスクが有るなら処理。無いなら終了=スレッドの終了。
class Worker {
protected:
    int _number;
    boost::mutex _mtx;
    boost::condition _cond;
    bool _working;
    bool _finishable;
    TaskBag* _taskBag;
    TaskData* _task;
public:
    Worker(int number, TaskBag* taskBag) {
        _finishable = false;
        _number = number;
        _taskBag = taskBag;
    };
    virtual ~Worker() { };
    
    void run();
    virtual void job() = 0;
    void finish() {
        boost::mutex::scoped_lock lock(_mtx);
        _finishable = true;
        _cond.notify_all();
    };
    void wake() {
        boost::mutex::scoped_lock lock(_mtx);
        _working = true;
        _cond.notify_all();
    };
};

//ワークパイル管理。
template <class T>
class WorkPileManager {
    int _numThreads;
    boost::thread_group _threadG;
    T** _workers;
    TaskBag _taskBag;
public:
    WorkPileManager(int numThreads = 0) {
        _numThreads = numThreads < 1 ? boost::thread::hardware_concurrency() : numThreads;
        _workers = (T**)malloc(_numThreads * sizeof(T*));
        for (int i = 0; i < _numThreads; ++i) {
            _workers[i] = new T(i, &_taskBag);
            _threadG.create_thread(boost::bind(&T::run, _workers[i]));
        }
    };
    
    //デストラクターが動作するようにこのクラスによるワークパイル処理を実行する箇所はスコープで囲むこと．
    //スレッド処理の箇所を明確化させるため．
    ~WorkPileManager() {
        _threadG.join_all();
        for (int i = 0; i < _numThreads; ++i) {
            delete _workers[i];
        }
        free(_workers);
    };
    
    void pushTask(TaskData* task) {
        _taskBag.pushTask(task);
        wakeWorkers();
    };
    
    void finish() {
        for (int i = 0; i < _numThreads; ++i) {
            _workers[i]->finish();
        }
    };
    
    void wakeWorkers() {
        for (int i = 0; i < _numThreads; ++i) {
            _workers[i]->wake();
        }
    };
    
    int numThreads() {
        return _numThreads;
    };
};

#endif
