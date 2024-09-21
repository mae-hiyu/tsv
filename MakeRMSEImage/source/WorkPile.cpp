//
//  WorkPile.cpp
//  GIRenderer
//
//  Created by 渡部心 on 12/02/10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "WorkPile.hpp"
using namespace boost;

void TaskBag::pushTask(TaskData *task) {
    mutex::scoped_lock lock(_mtx);
    _tasks.push_back(task);
}

bool TaskBag::getTasks(TaskData **task) {
    mutex::scoped_lock lock(_mtx);
    if (_tasks.size() != 0) {
        *task = _tasks[0];
        _tasks.erase(_tasks.begin());
        return true;
    }
    else {
        *task = NULL;
        return false;
    }
}

int TaskBag::numTasks() {
    mutex::scoped_lock lock(_mtx);
    return int(_tasks.size());
}

void Worker::run() {
    while (true) {
        //------------------------------------------
        //仕事を取得して処理を繰り返す。
        while (_taskBag->getTasks(&_task)) {
            job();
        }
        _working = false;
        //------------------------------------------
        
        //------------------------------------------
        //仕事が無くfinishableならスレッドの関数を終了する。
        if (_finishable && _taskBag->numTasks() == 0) {
            break;
        }
        //------------------------------------------
        
        //------------------------------------------
        //wakeかfinishを呼ばれるまでスレッド休止。
        //whileの条件判定後からwaitをかけるまでの間に_finishable = true, notifyを呼ばれないように
        //_mtxにロックをかける。
        mutex::scoped_lock lock(_mtx);
        while (!_working && !_finishable) {
            _cond.wait(lock);    
        }
        //------------------------------------------
    }
}
