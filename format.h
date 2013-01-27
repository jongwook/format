#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>

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
std::string to_string(std::shared_ptr<Arg> arg) {
	char buf[20];
	sprintf(buf, "0x%016llx", (unsigned long long)&*arg);
	return std::string(buf);
}

template<>
std::string to_string(std::string arg) {
	return arg;
}

template<>
std::string to_string(const char * arg) {
	if (arg == nullptr) {
		return "(null)";
	}
	return std::string(arg);
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
	
public:	
	explicit Format(string_type format) : format_(format) {}
	explicit Format(vector_type && tokens, string_type format) : tokens_(tokens), format_(format) {}
	
	string_type format() const {
		return format_;
	}
	
	const vector_type & tokens() const {
		return tokens_;
	}

	template <typename Arg>
	Format operator % (const Arg arg) {
		size_t pos = format().find("{}");
		if (pos == string_type::npos) {
			return std::move(*this); // ignure unmatched arguments
		}
		
		tokens_.push_back(format().substr(0, pos));
		tokens_.push_back(to_string(arg));
		
		return Format(std::move(tokens_), format().substr(pos + 2));
	}

	operator std::string() const {
		std::stringstream ss;
		for (auto token : tokens()) {
			ss << token;
		}
		ss << format();
		return ss.str();
	}

private:
	vector_type tokens_;
	const string_type format_;
};

std::ostream& operator << (std::ostream &os, const Format &format) {
	return os << static_cast<std::string>(format);
}
