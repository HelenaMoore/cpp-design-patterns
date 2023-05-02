#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Query
{
    std::string command_select = "SELECT";
    std::vector<std::string> column;
    std::string command_from;
    std::map<std::string, std::string> command_where;
};

class SqlSelectQueryBuilder
{
private:
    Query query;
public:
    explicit SqlSelectQueryBuilder() {};
    SqlSelectQueryBuilder& AddColumn(const std::string& column_name);
    SqlSelectQueryBuilder& AddFrom(const std::string& table);
    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value);

    std::string constructColumns();
    std::string constructWhere();
    std::string BuildQuery() noexcept;
};