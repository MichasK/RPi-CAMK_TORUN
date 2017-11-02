#ifndef files_operations_h
#define files_operations_h
void SaveToFile(std::string message, int lines_treshold,
		std::string output_file_name);
bool IsPhoto(string &file_name);
void Search_Config(int argc, char* argv[], Configuration &config);
void set_config(Configuration &config);
#endif
