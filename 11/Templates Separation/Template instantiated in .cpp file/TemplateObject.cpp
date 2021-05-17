#include "TemplateObject.h"

template <typename T>
TemplateObject<T>::TemplateObject(const T& value)
	: data(value)
{}

// тук ни е нужен единствено конкретният тип, 
// за да може да се създаде клас по шаблона...

//TemplateObject<int> o(2);
//TemplateObject<double> o1(2);

// или

template struct TemplateObject<int>;
template struct TemplateObject<double>;

// но можем ли да изброим всички възможни типове,
// с които би могъл да се използва шаблонът?