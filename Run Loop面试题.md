# Run Loop面试题
1. 什么是Run Loop？
	* 从字面上看：运行循环、跑圈。
	* 它的内部是do－while循环，在这个循环内部不断处理各种任务。（Source、Timer、Observer）
	* 一个线程对应一个Run Loop，主线程的Run Loop默认启动。子线程的Run Loop需要手动启动，调用run方法。
	
		```c
		//CFRunLoop.c
		//创建主线程Run Loop
		CFMutableDictionaryRef dict = CFDictionaryCreateMutable(kCFAllocatorSystemDefault, 0, NULL, &kCFTypeDictionaryValueCallBacks);
	CFRunLoopRef mainLoop = __CFRunLoopCreate(pthread_main_thread_np());
	CFDictionarySetValue(dict, pthreadPointer(pthread_main_thread_np()), mainLoop);
	//子线程Run Loop的创建
	if (!loop) {
	    CFDictionarySetValue(__CFRunLoops, pthreadPointer(t), newLoop);
	    loop = newLoop;
	}
	//新线程做Key，newLoop为Value，所以线程与Run Loop一一对应。
		```
	* Run Loop只能选择一个Model启动，如果当前Model中没有任何Source(Source0，Source0)、Timer、就会退出Run Loop。(注意：即使有Observer也会退出Run Loop，Source、Timer主动给Run Loop发消息，Observer被动接收消息)
	
		```
		//CFRunLoop.c
		static Boolean __CFRunLoopModeIsEmpty(CFRunLoopRef rl, CFRunLoopModeRef rlm, CFRunLoopModeRef previousMode) {
    CHECK_FOR_FORK();
    if (NULL == rlm) return true;
#if DEPLOYMENT_TARGET_WINDOWS
    if (0 != rlm->_msgQMask) return false;
#endif
    Boolean libdispatchQSafe = pthread_main_np() && ((HANDLE_DISPATCH_ON_BASE_INVOCATION_ONLY && NULL == previousMode) || (!HANDLE_DISPATCH_ON_BASE_INVOCATION_ONLY && 0 == _CFGetTSD(__CFTSDKeyIsInGCDMainQ)));
    if (libdispatchQSafe && (CFRunLoopGetMain() == rl) && CFSetContainsValue(rl->_commonModes, rlm->_name)) return false; // represents the libdispatch main queue
    //判断sources0、sources1、timers，没有判断Observer
    if (NULL != rlm->_sources0 && 0 < CFSetGetCount(rlm->_sources0)) return false;
    if (NULL != rlm->_sources1 && 0 < CFSetGetCount(rlm->_sources1)) return false;
    if (NULL != rlm->_timers && 0 < CFArrayGetCount(rlm->_timers)) return false;
    struct _block_item *item = rl->_blocks_head;
    while (item) {
        struct _block_item *curr = item;
        item = item->_next;
        Boolean doit = false;
        if (CFStringGetTypeID() == CFGetTypeID(curr->_mode)) {
            doit = CFEqual(curr->_mode, rlm->_name) || (CFEqual(curr->_mode, kCFRunLoopCommonModes) && CFSetContainsValue(rl->_commonModes, rlm->_name));
        } else {
            doit = CFSetContainsValue((CFSetRef)curr->_mode, rlm->_name) || (CFSetContainsValue((CFSetRef)curr->_mode, kCFRunLoopCommonModes) && CFSetContainsValue(rl->_commonModes, rlm->_name));
        }
        if (doit) return false;
    }
    return true;
}

		```
2. 开发中Run Loop的使用场景： 
	*  开启一个常驻线程。（让一个子线程不进入消亡状态，等待其他线程发来消息，处理其它事件）
		* 在子线程中开启一个定时器。
		* 在子线程中进行长期监控。（监控网络状态）
	* 可以让定时器在特定模式下执行。
	* 可以让某些事件（行为、任务）在特定模式下执行。
	* 可以添加Observer监听Run Loop状态，比如监听点击事件的处理。（在所有点击事件之前做一些事情）
3. 自动释放池什么时候释放？
	* 	通过Observer监听Run Loop的状态，一旦监听到Run Loop即将进入睡眠状态，就释放自动释放池。(kCFRun LoopBeforeWaiting)
	* NSLog输出当前Run Loop我们大致会得到以下信息
	
		```
		0 : <CFRunLoopObserver 0x7fcbaa613030 [0x105041a40]>{valid = Yes, activities = 0x1, repeats = Yes, order = -2147483647, callout = _wrapRunLoopWithAutoreleasePoolHandler (0x1051c84c2), context = <CFArray 0x7fcbaa612ec0 [0x105041a40]>{type = mutable-small, count = 0, values = ()}}
		5 : <CFRunLoopObserver 0x7fcbaa6130d0 [0x105041a40]>{valid = Yes, activities = 0xa0, repeats = Yes, order = 2147483647, callout = _wrapRunLoopWithAutoreleasePoolHandler (0x1051c84c2), context = <CFArray 0x7fcbaa612ec0 [0x105041a40]>{type = mutable-small, count = 0, values = ()}}
		```
	* 	activities = 0x1,（1）activities = 0xa0（160）。
	
		```
		kCFRunLoopEntry = (1UL << 0),1
    kCFRunLoopBeforeTimers = (1UL << 1),2
    kCFRunLoopBeforeSources = (1UL << 2),4
    kCFRunLoopBeforeWaiting = (1UL << 5),32
    kCFRunLoopAfterWaiting = (1UL << 6),64
    kCFRunLoopExit = (1UL << 7),128
		```
	* 所以可以知道activities = 0x1，对应kCFRunLoopEntry，而160对应的是128与32的和，所以对应kCFRunLoopBeforeWaiting 和 kCFRunLoopExit。
	* 结论：
		* kCFRunLoopEntry 创建自动释放池。
		* kCFRunLoopBeforeWaiting 销毁旧的自动释放池，并创建一个新的自动释放池。
		* kCFRunLoopExit销毁自动释放池。


