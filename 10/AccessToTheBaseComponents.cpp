#include <iostream>

class Base
{
    private:
        int m_private;

    protected:
        int m_protected;

    public:
        int m_public;
};

class Private: private Base
{
    public:
        // до какво имаме достъп в класа Private?
        Private()
        {
            // няма достъп до член-данни в private частта на базовия клас
            //m_private = 0;

            // има директен достъп до protected и public
            m_protected = 1;
            m_public = 2;
        }
};

class Protected: protected Base
{
    public:
        // до какво имаме достъп в класа Protected?
        Protected()
        {
            // няма достъп до член-данни в private частта на базовия клас
            //m_private = 0;

            // има директен достъп до protected и public
            m_protected = 1;
            m_public = 2;
        }
};

class Public: public Base
{
    public:
        // до какво имаме достъп в класа Public?
        Public()
        {
            // няма достъп до член-данни в private частта на базовия клас
            //m_private = 0;

            // има директен достъп до protected и public
            m_protected = 1;
            m_public = 2;
        }
};

int main()
{
    Private pri;
    // private на базовия клас, няма външен достъп
    //pri.m_private = 0;
    
    // при private наследяване protected и public
    // стават част от private частта на производния клас
    // няма външен достъп до тях
    //pri.m_protected = 1;
    //pri.m_public = 2;

    Protected pro;
    // private на базовия клас, няма външен достъп
    //pro.m_private = 0;
    
    // при protected наследяване protected и public
    // стават част от protected частта на производния клас
    // няма външен достъп до тях
    //pro.m_protected = 1;
    //pro.m_public = 2;

    Public pub;
    // private на базовия клас, няма външен достъп
    //pub.m_private = 0;
    
    // при public наследяване
    // protected член-данните стават част от protected частта на производния клас,
    // няма достъп до тях

    // public член-данните стават част от public частта на производния клас
    // има външен достъп до тях
    //pub.m_protected = 1;
    pub.m_public = 2;

    return 0;
}
