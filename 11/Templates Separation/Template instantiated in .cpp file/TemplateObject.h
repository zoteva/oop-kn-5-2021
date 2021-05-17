#ifndef TEMPLATEOBJECT_H
#define TEMPLATEOBJECT_H

template <typename T>
struct TemplateObject
{
	TemplateObject(const T&);
	T data;
};

#endif // !TEMPLATEOBJECT_H
