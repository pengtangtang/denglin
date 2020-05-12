/*eg1:
 * void f(int i,std::string const& s);
 * std::thread t(f,3,"hello");
 *
 * eg2:指向动态变量的指针作为参数
 * void f(int i,std::string const& s);
 * void oops(int some_param)
 * {
 *	char buffer[1024];
 *	sprintf(buffer,"%i",some_param);
 *	std::thread t(f,3,std::string(buffer));//将字面值转换为函数参数类型
 *	t.detach();
 * }
 *
 * eg3:引用传递的数据结构为参数
 * void update_data_for_widget(widget_id w,widget_data& data);
 * void oops_again(widget_id w)
 * {
 *	widget_data data;
 *	std::thread t(update_data_for_widget,w,std::ref(data));//ref()将参数转换为引用
 *	dispaly_status();
 *	t.join();
 *	process_widget_data(data);
 * }
 * */
//eg4:将动态对象转移到线程中---对象所有权将转移
void process_big_object(std::unique_ptr<big_object>);
std::unique_ptr<big_object> p(new big_object);
p->prepare_data(42);
std::thread t(process_big_object,std::move(p));
