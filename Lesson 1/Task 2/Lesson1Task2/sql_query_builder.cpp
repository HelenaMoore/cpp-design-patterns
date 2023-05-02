#include "sql_query_builder.h"

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& column_name)
{
    query.column.push_back(column_name);
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::vector<std::string>& columns) noexcept
{
    for (auto iterator = columns.begin(); iterator != columns.end(); ++iterator)
    {
        std::string column = *iterator;
        query.column.push_back(column);
    }
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& table)
{
    query.command_from = table;
    return *this;
}

    SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& column, const std::string& value)
{
    query.command_where[column] = value;
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv) noexcept
{
    for (auto iterator = kv.begin(); iterator != kv.end(); ++iterator)
    {
        std::string key = iterator->first;
        std::string value = iterator->second;
        query.command_where[key] = value;
    }
    return *this;
}

std::string SqlSelectQueryBuilder::constructColumns()
{
    if (query.column.empty())
    {
        return "*";
    }

    if (query.column.size() == 1)
    {
        return query.column[0];
    }

    std::string result = "";

    size_t i = 0;

    for (auto iterator = query.column.begin(); iterator != query.column.end(); ++iterator)
    {
        ++i;
        result += *iterator;
        if (i != query.column.size())
        {
            result += ", ";
        }
    }

    return result;
}

std::string SqlSelectQueryBuilder::constructWhere()
{
    if (query.command_where.empty())
    {
        return "";
    }

    auto iterator = query.command_where.begin();
    std::string result = "WHERE " + iterator->first + "=" + iterator->second;
    if (iterator == query.command_where.end())
    {
        return result;
    }

    for (auto iterator = query.command_where.begin(); iterator != query.command_where.end(); ++iterator)
    {
        if (iterator != query.command_where.begin())
        {
            result = result + " AND " + iterator->first + "=" + iterator->second;
        }
    }

    return result;
}

std::string SqlSelectQueryBuilder::BuildQuery() noexcept
{
    if (!query.command_from.empty())
    {
        std::string result = query.command_select + " " + constructColumns() + " FROM " + query.command_from + " " + constructWhere() + ";";
        return result;
    }
    return "Source table is not specified.";
}