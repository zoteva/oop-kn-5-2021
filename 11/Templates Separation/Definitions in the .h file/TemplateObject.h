#ifndef TEMPLATEOBJECT_H
#define TEMPLATEOBJECT_H

template <typename T>
struct TemplateObject
{
	TemplateObject(const T&);
	T data;
};

template <typename T>
inline TemplateObject<T>::TemplateObject(const T& value)
	: data(value)
{}


#endif // !TEMPLATEOBJECT_H
