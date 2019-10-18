#include "empmaps.cpp"

int main()
{
	std::vector<Employee> empVec = employees();

	std::map<int, std::vector<Employee>> deptMap = mapEmpDept(empVec);
	std::map<int, std::vector<Employee>> salMap = mapSalRange(empVec);
	printSalRange(salMap);
	
}
