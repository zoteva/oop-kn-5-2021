#include "TemplateObject.h"

template <typename T>
TemplateObject<T>::TemplateObject(const T& value)
	: data(value)
{}
