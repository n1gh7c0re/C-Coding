#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport)
#else
#define MATHLIBRARY_API __declspec(dllimport)
#endif
//создает прототип функций дл€ алгоритма сортировки
typedef void (*sort_func_t)(int array[], int size);

//определ€ет семейства сортировок
typedef enum {
	SORT_NA = -1,
	SORT_SELECTION,
	SORT_INSERTION,
	SORT_BUBBLE,
	SORT_SHELL,
	SORT_COMB,
	SORT_MERGE,
	SORT_QUICK,
	SORT_HEAP,
	SORT_COUNT,
	SORT_RADIX,
	SORT_BUCKET
} sort_family_t;

//вычислительна€ сложность
typedef enum {
	SORT_QUADRATIC,
	SORT_SUBQUADRATIC,
	SORT_QUASILINEAR,
	SORT_LINEAR
} sort_complexity_t;

//вариаци€ сортировки Ц структура, содержаща€ нужную информацию
typedef struct {
	sort_func_t sort;
	sort_family_t family;
	sort_complexity_t complexity;
	char const* name;
}sort_info_t;

__declspec(dllexport) sort_info_t* GetSortList(int* count);