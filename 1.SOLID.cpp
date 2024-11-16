#include <fstream>
#include <iostream>

class IFormatter 
{
public:
    virtual ~IFormatter() = default;
    virtual std::string format(const std::string& data) const = 0;
};

class TextFormatter : public IFormatter
{
    std::string format(const std::string& data) const override
    {
        return data;
    }
};

class HTMLFormatter : public IFormatter 
{
public:
    std::string format(const std::string& data) const override 
    {
        return "<html>" + data + "</html>";
    }
};

class JSONFormatter : public IFormatter 
{
public:
    std::string format(const std::string& data) const override 
    {
        return "{ \"data\": \"" + data + "\" }";
    }
};

class Data
{
public:
    Data(std::string data) : data_(std::move(data)){}

    const std::string& getData() 
       const 
    {
        return data_;
    }
private:
    std::string data_;

};

static void saveTo(std::ofstream& file, const Data& data, const IFormatter& formatter)
{
    file << formatter.format(data.getData());
}

static void saveToAsHTML(std::ofstream& file, const Data& data)
{
    HTMLFormatter formatter;
    saveTo(file, data, formatter);
}

static void saveToAsJSON(std::ofstream& file, const Data& data)
{
    JSONFormatter formatter;
    saveTo(file, data, formatter);
}

static void saveToAsText(std::ofstream& file, const Data& data)
{
    TextFormatter formatter;
    saveTo(file, data, formatter);
}
