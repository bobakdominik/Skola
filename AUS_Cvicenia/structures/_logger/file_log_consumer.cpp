#include "file_log_consumer.h"


namespace structures 
{
	FileLogConsumer::FileLogConsumer(const std::string& path) :
		fileStream_(path)
	{
		if (!this->fileStream_.is_open())
		{
			throw std::invalid_argument("FileLogConsumer::FileLogConsumer: Failed to open file " + path);
		}
	}

	void FileLogConsumer::logMessage(LogType type, const std::string& message)
	{
		this->fileStream_ << logTypeToString(type) << ";" << message << std::endl;
	}

	void FileLogConsumer::logDuration(size_t size, DurationType duration, const std::string& message)
	{
		this->fileStream_ << "Duration;" << size << ";" << duration.count() << ";" << message << std::endl;
	}
}

