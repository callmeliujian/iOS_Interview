1. Objective-C变量前面加"_"是什么意思？
	- 声明的property如果没有指定synthesize，就会自动声明_开头的实例变量。
	- 假如你声明了一个@property(nonatomic, copy) NSString *name;通过_name进行存取不会调用setter／getter方法，声明的copy也不会起作用，self.name会调用setter／getter方法，copy起作用。
	- @synthesize name ＝ name；就不会生成_name，取而代之的是name。
2. @property内存管理策略
	- 非ARC
		1. copy：只用于NSString/block。
		2. retain：除NSString/block以外的OC对象。
		3. assign：基本数据类型、枚举、结构体（非OC对象），当2个对象相互引用，					一端用retain，一端用assign。
		
	- ARC
		1. copy：只用于NSString/block。
		2. strong：用于除NSString/block以外的对象。
		3. weak：当两个对象互相饮用，一端用strong，一端用weak。
		4. assign：基本数据类型、枚举、结构体（非OC对象）。
3. copy/mutableCopy
 - 利用原对象产生一个副本对象（副本对象中的内容和原对象内容一致），修改原对象的属性和行为不会影响副本对象，修改副本对象不会影响原对象。
 - 一般情况下copy/mutableCopy操作会生成一个新的对象，但是不可变对象通过copy不会生成新对象。
 		- 产生新对象的原因
			1. 修改原对象不会影响副本对象，修改副本对象不会影响原对象。
			2. 不可变对象通过mutableCopy生成可变对象，所以必须生成新对象（可变对象通过copy生成不可变对象同理）。
			3. 可变对象通过mutableCopy生成可变对象，当修改原／副本对象的时候不能相互影响所以要生成新对象。
			4. 不可变对象通过copy生成不可变对象，因为两个对象是都不能修改的，所以不会生成新对象（oc的内存优化）。
	- 正因为copy有时会生成新对象，有时不会生成新对象，所以就出现了浅拷贝与深拷贝
		- 浅拷贝：没有生成新对象，本质就是指针拷贝。
			- 注意：`原对象引用计数＋1(相当于进行retain操作)。`
		- 深拷贝：生成新对象，本质就是创建了一个新对象。
			- 注意：原对象引用计数不变。     
 - 如果想令自己的类支持拷贝操作就要实现NSCopying或NSMutableCopying协议。如果自定义的对象分为可变和不可变两个版本，就要同时实现NSCopying和NSMutableCopying协议。
	- NSCopying协议中只有一个方法（生成不可变对象）
	
		```
		- (id)copyWithZone:(nullable NSZone *)zone;
		```
		实现：
		
		```
		//Person.h
		@property (nonatomic, assign) int age;
		@property (nonatomic, copy) NSString *name;
		
		//Person.m
		- (id)copyWithZone:(NSZone *)zone
		{
    		// 1.创建一个新的对象
    		Person *p = [[[self class] allocWithZone:zone] init];
    		// 2.设置当前对象的内容给新的对象
    		p.age = _age;
    		p.name = _name;
    		// 3.返回新的对象
    		return p;
		}
		```
	- 	NSMutableCopying协议中只有一个方法（生成可变对象）
		
		```
		- (id)mutableCopyWithZone:(nullable NSZone *)zone;
		```
		实现：
		
		```
		//Person.h
		@property (nonatomic, assign) int age;
		@property (nonatomic, copy) NSString *name;
		
		//Person.m
		- (id)mutableCopyWithZone:(NSZone *)zone
		{
		    // 1.创建一个新的对象
		    Person *p = [[[self class] allocWithZone:zone] init];
		    // 2.设置当前对象的内容给新的对象
		    p.age = _age;
		    p.name = _name;
		    // 3.返回新的对象
		    return p;
		}
		```
	- 举例
	
		```
		[NSArray mutableCopy] -> NSMutableArray
		[NSMutableArray copy] -> NSArray
		```
	- 浅拷贝：只拷贝容器对象本身，而不复制其中的数据。
	
		```
		//Person.h
		@property (nonatomic, assign) int age;
		@property (nonatomic, copy) NSString *name;
		
		//Person.m
		- (id)copyWithZone:(NSZone *)zone
		{
		    // 1.创建一个新的对象
    		Person *p = self;
    		// 2.返回新的对象
    		return p;
		}
		```
	- 深拷贝：在拷贝对象自身的时候，将底层数据也复制过去。
	
		```
		//Person.h
		@property (nonatomic, assign) int age;
		@property (nonatomic, copy) NSString *name;
		
		//Person.m
		- (id)deepCopy
		{
		    // 1.创建一个新的对象
		    Person *p = [[[self class] allocWithZone:zone] init];
		    // 2.设置当前对象的内容给新的对象
		    p.age = _age;
		    p.name = _name;
		    // 3.返回新的对象
		    return p;
		}
		```
![屏幕快照 2016-07-31 上午11.39.37](media/%E5%B1%8F%E5%B9%95%E5%BF%AB%E7%85%A7%202016-07-31%20%E4%B8%8A%E5%8D%8811.39.37.png)


	- 复制对象的时候一般执行浅拷贝。
	- 如果你的对象需要深拷贝，应该考虑专门执行深拷贝的方法。
	- 字符串属性都要使用copy。（防止外界修改内部数据）
	- 使用copy保存block，这样可以保住block中使用的外界对象，避免以后调用block的时候，对象已经被外界释放。（Block_release(blcok)，MRC中使用，释放block，并且block中的对象也可以接收到release消息）
		- 注意：copy block之后会产生循环引用（对象中的block又用到了对象自己），为了避免内存泄漏应该讲对象修饰为__block.
	- 子类会继承父类的协议，当父类实现了copy的方法，子类也就相应的实现了。但是如果子类有新的属性，那么必须在子类中重写copyWithZone方法, 在该方法中先调用父类创建副本设置值, 然后再设置子类特有的值。
		- 举例（Son为上文中Person的子类）
			
		```
		Son.h
		@property (nonatomic, assign) double height;
		
		Son.m
		- (id)copyWithZone:(NSZone *)zone
		{
		    // 1.创建一个新的对象
		    id obj = [super copyWithZone:zone];
		    // 2.设置新对象的数据
		    [obj setHeight:_height];
		    // 3.返回新对象
		    return obj;
		}
		```
4. 集合（（可变）数组、（可变）字典、NSSet）对象的内存管理：
	- 将一个对象添加到一个集合中，集合会对对象进行一次retain操作（引用计数加一）。
	- 当集合释放对象之后会给集合中所有的对象发送release消息（引用计数减一）。
	- 当集合移除一个对象之后，会给这个对象发送release消息（引用计数减一）。
5. block默认存储在栈中，栈中的block访问外界对象，不会对外界对象进行retian操作。如果block在堆中，并且访问了外界对象，就会对外界对象进行一次retain操作。

	```
	//将block转移到堆中
	Block_copy(block);
	```
6. 代理设计模式的作用：
	- A对象监听B对象的行为，A成为B的代理。
	- B对象告诉A对象一些信息，A成为B的代理。
7. 代理设计模式的开发步骤：
	1. 创建协议（协议名称的格式：控件名＋Delegate），协议里面声明代理方法（一般代理方法用@optional）。
	2. 声明一个代理属性：@property(nonatomic, weak) id<代理协议>delegate;。
	3. 在内部发生某些行为的时候，调用代理对应的代理方法，通知代理内部发生的事情。
	4. 设置代理：xxx.delegate = yyy;
	5. yyy对象遵守协议，实现代理方法。
	6. 判断是否实现协议的某个方法。
	
	```objc
	if ([self.delegate respondsToSelector:@selector(方法名)]) {
   [self.delegate 方法名];
}
	``` 
8. KVC/KVO
	* KVC(Key Value Coding)：给模型属性赋值。
	* KVO(Key Value Observing)：监听模型属性改变。
		* KVO使用步骤：
		
			```objc
			// b对象监听了a对象的name属性的改变
			[a addObserver:b forKeyPath:@"name" options: NSKeyValueObservingOptionOld context:nil];

			// b对象实现监听方法
			- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
			{
			    //some code
			}
			
			//移除监听
			[a removeObserver:b forKeyPath:@"name"];
			``` 		 


