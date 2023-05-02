#include "sql_query_builder.h"

int main(int argc, char** argv)
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::cout << query_builder.BuildQuery() << std::endl;

    std::map<std::string, std::string> conditions{ {"phone", "233-233-233"}, {"age", "28"} };
    std::vector<std::string> columns{ "age", "id" };

    query_builder.AddWhere(conditions);
    query_builder.AddColumn(columns);

    std::cout << query_builder.BuildQuery();

    return 0;
}