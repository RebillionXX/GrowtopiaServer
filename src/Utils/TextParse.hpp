#pragma once
#include <string>
#include <vector>

class TextParse {
public:
    TextParse();
    explicit TextParse(const std::string& string);
    explicit TextParse(const std::vector<std::pair<std::string, std::string>>& data);
    ~TextParse();

    static std::vector<std::string> StringTokenize(const std::string& string, const std::string& delimiter = "|");

public:
    void Parse(const std::string& string);

    std::string Get(const std::string& key, int index = 1, const std::string& token = "|", int key_index = 0);
    template <typename T, typename std::enable_if_t<std::is_integral_v<T>, bool> = true>
    T Get(const std::string& key, int index = 1, const std::string& token = "|") {
        return std::stoi(this->Get(key, index, token));
    }
    template <typename T, typename std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
    T Get(const std::string& key, int index = 1, const std::string& token = "|");

    void Add(const std::string& key, const std::string& value, const std::string& token = "|") {
        m_data.push_back(key + token + value);
    }
    template <typename T, typename std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, bool> = true>
    void Add(const std::string& key, const T& value, const std::string& token = "|") {
        this->Add(key, std::to_string(value), token);
    }

    void Set(const std::string& key, const std::string& value, const std::string& token = "|");
    template <typename T, typename std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>, bool> = true>
    void Set(const std::string& key, const T& value, const std::string& token = "|");

    bool Contain(const std::string& key) {
        return this->Get(key) != "" ? true : false;
    }
public: 
    bool IsEmpty() const;

    size_t GetSize() const;
    std::string GetAsString() const;

private:
    std::vector<std::string> m_data;
};