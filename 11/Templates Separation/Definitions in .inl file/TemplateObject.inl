// в този файл се дефинират функциите от съответния шаблон
// той се включва в TemplateObject.h

template <typename T>
inline TemplateObject<T>::TemplateObject(const T& value)
	: data(value)
{}
