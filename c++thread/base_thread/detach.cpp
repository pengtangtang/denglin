/*detach:
 * 不能对没有执行线程的thread对象使用detach() join()
 * 且使用joinable()进行检查
 *
 * std::thread t(do_background_work);
 * t.detach();
 * asssert(!t.joinable());
 *
 * */

//使用分离线程处理其他文档

void edit_document(std::string const& filename)
{
	open_document_and_display_gui(filename);
	while (!done_editing())
	{
		user_command cmd = get_user_input();
		if (cmd.type == open_new_document)
		{
			std::string const new_name = get_filename_from_user();
			std::thread t(edit_document,new_name);
			t.detach();
		}
		else
			process_user_input(cmd);
	}


}
