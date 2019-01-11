/*
 * Copyright 2017 Andrei Pangin
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ARGUMENTS_H
#define _ARGUMENTS_H

#include <stddef.h>


const long DEFAULT_INTERVAL = 10000000;  // 10 ms
const int DEFAULT_FRAMEBUF = 1000000;

const char* const EVENT_CPU    = "cpu";
const char* const EVENT_ALLOC  = "alloc";
const char* const EVENT_LOCK   = "lock";
const char* const EVENT_WALL   = "wall";
const char* const EVENT_ITIMER = "itimer";

enum Action {
    ACTION_NONE,
    ACTION_START,
    ACTION_STOP,
    ACTION_STATUS,
    ACTION_LIST,
    ACTION_VERSION,
    ACTION_DUMP
};

enum Counter {
    COUNTER_SAMPLES,
    COUNTER_TOTAL
};

enum Ring {
    RING_ANY,
    RING_KERNEL,
    RING_USER
};


class Error {
  private:
    const char* _message;

  public:
    static const Error OK;

    explicit Error(const char* message) : _message(message) {
    }

    const char* message() {
        return _message;
    }

    operator bool() {
        return _message != NULL;
    }
};


class Arguments {
  private:
    char _buf[1024];

    long parseUnits(const char* str);

  public:
    Action _action;
    Counter _counter;
    Ring _ring;
    const char* _event;
    long _interval;
    int  _jstackdepth;
    int _framebuf;
    bool _threads;
    bool _simple;
    bool _annotate;
    char* _file;
    bool _dump_collapsed;
    bool _dump_flamegraph;
    bool _dump_tree;
    bool _dump_jfr;
    bool _dump_summary;
    bool _dump_immediate_trace;
    int _dump_traces;
    int _dump_flat;
    // FlameGraph parameters
    const char* _title;
    int _width;
    int _height;
    double _minwidth;
    bool _reverse;

    Arguments() :
        _action(ACTION_NONE),
        _counter(COUNTER_SAMPLES),
        _ring(RING_ANY),
        _event(EVENT_CPU),
        _interval(0),
        _jstackdepth(0),
        _framebuf(DEFAULT_FRAMEBUF),
        _threads(false),
        _simple(false),
        _annotate(false),
        _file(NULL),
        _dump_collapsed(false),
        _dump_flamegraph(false),
        _dump_tree(false),
        _dump_jfr(false),
        _dump_summary(false),
	_dump_immediate_trace(false),
        _dump_traces(0),
        _dump_flat(0),
        _title("Flame Graph"),
        _width(1200),
        _height(16),
        _minwidth(1),
        _reverse(false) {
    }

    bool dumpRequested() {
        return _dump_collapsed || _dump_flamegraph || _dump_tree || _dump_jfr || _dump_summary || _dump_traces > 0 || _dump_flat > 0;
    }

    Error parse(const char* args);
};

#endif // _ARGUMENTS_H
