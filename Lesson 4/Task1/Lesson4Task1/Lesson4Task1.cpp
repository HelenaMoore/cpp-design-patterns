#include <iostream>
#include <fstream>
#include <string>

class Printable
{
public:
    virtual ~Printable() = default;

    virtual std::string print() const = 0;
};

class DataHTML : public Printable
{
public:
    DataHTML(std::string data)
        : data_(std::move(data)) {}

    std::string print() const override
    {
        return "<html>" + data_ + "<html/>";
    }
private:
    std::string data_;
};

class DataText : public Printable
{
public:
    DataText(std::string data)
        : data_(std::move(data)) {}

    std::string print() const override
    {
        return data_;
    }
private:
    std::string data_;
};

class DataJSON: public Printable
{
public:
    DataJSON(std::string data)
        : data_(std::move(data)) {}

    std::string print() const override
    {
        return "{ \"data\": \"" + data_ + "\"}";
    }
private:
    std::string data_;
};

void saveTo(std::ofstream& file, const Printable& printable)
{
    file << printable.print();     
}

int main(int argc, char** argv)
{
    DataHTML data_html("sample html data");
    DataText data_text("sample text data");
    DataJSON data_json("sample json data");

    std::ofstream write_file("out.txt", std::ios::app);
    if (write_file.is_open())
    {
        saveTo(write_file, data_html);
        write_file << std::endl;
        saveTo(write_file, data_text);
        write_file << std::endl;
        saveTo(write_file, data_json);
    }
    write_file.close();

    return 0;
}