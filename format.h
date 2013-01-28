#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <memory>

template <typename Arg>
std::string to_string(Arg arg) {
	return std::to_string(arg);
}

template<typename Arg>
std::string to_string(Arg * arg) {
	char buf[20];
	sprintf(buf, "0x%016llx", (unsigned long long)arg);
	return std::string(buf);
}

template<typename Arg>
std::string to_string(const std::shared_ptr<Arg> &arg) {
	char buf[20];
	sprintf(buf, "0x%016llx", (unsigned long long)&*arg);
	return std::string(buf);
}

template<typename Arg>
std::string to_string(const std::unique_ptr<Arg> &arg) {
	char buf[20];
	sprintf(buf, "0x%016llx", (unsigned long long)&*arg);
	return std::string(buf);
}

template<typename Arg>
std::string to_string(const std::weak_ptr<Arg> &arg) {
	if (auto sp = arg.lock()) {
		char buf[20];
		sprintf(buf, "0x%016llx", (unsigned long long)&*sp);
		return buf;
	} 
	return "(expired)";
}

template<>
std::string to_string(std::string arg) {
	return arg;
}

template<>
std::string to_string(char * arg) {
	if (arg == nullptr) {
		return "(null)";
	}
	return arg;
}

template<>
std::string to_string(char arg) {
	return std::string(&arg, 1);
}

class Format {
public:
	typedef std::string string_type;
	typedef std::vector<string_type> vector_type;
	
	explicit Format(Format && format) : tokens_(std::move(format.tokens_)), format_(std::move(format.format_)) {}
	explicit Format(string_type format) : format_(format) {}
	explicit Format(vector_type && tokens, string_type format) : tokens_(tokens), format_(format) {}
	
	template <typename Arg>
	Format operator % (const Arg &arg) {
		size_t pos = format_.find("{}");
		if (pos == string_type::npos) {
			return std::move(*this); // ignore unmatched arguments
		}
		
		tokens_.push_back(format_.substr(0, pos));
		tokens_.push_back(to_string(arg));
		
		return Format(std::move(tokens_), format_.substr(pos + 2));
	}

	operator string_type() const {
		std::stringstream ss;
		for (auto token : tokens_) {
			ss << token;
		}
		ss << format_;
		return ss.str();
	}

private:
	vector_type tokens_;
	const string_type format_;
};

std::ostream& operator << (std::ostream &os, const Format &format) {
	return os << static_cast<std::string>(format);
}
