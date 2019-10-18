#include "empmaps.h"

int main()
{
	// Create the employee vector
	std::vector<Employee> empVec = employees();

	// Create the two different maps based on department and salary
	std::map<int, std::vector<Employee>> deptMap = mapEmpDept(empVec);
	std::map<int, std::vector<Employee>> salMap = mapSalRange(empVec);

	// Print the salary map
	printSalRange(salMap);

	// Create teh two different unordered maps based on department and salary
	std::unordered_map<int, std::vector<Employee>> deptUnMap = umapEmpDept(empVec);
	std::unordered_map<int, std::vector<Employee>> salUnMap = umapSalRange(empVec);

	// Print the salary unordered map
	uprintSalRange(salUnMap);
	
}
