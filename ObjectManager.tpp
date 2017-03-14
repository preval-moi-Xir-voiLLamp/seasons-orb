 template <typename T>
ObjectManager<T>::~ObjectManager(void)
{
    for(auto &i: m_AliveList)
    {
        delete i;
    }
}

template<typename T>
template<typename U, typename... Args>
U* ObjectManager<T>::add(Args&& ... args
    /*!< The list of the argument to give to the constructor of U*/)
{
    U *created = new U(args...);
    m_AliveList.push_back(created);
    return created;
}

template<typename T>
void ObjectManager<T>::update(float dt)
{
    /* We will update all the object and stock the dead one in dead list, then
     * delete all objects of the dead list
     */
    std::list<typename std::list<T *>::iterator> deadList;

    //First itteration: Update all objects
    for(auto i = m_AliveList.begin(); i != m_AliveList.end(); i++)
    {
        (*i)->update(dt);

        if((*i)->isDead())
        {
            deadList.push_front(i);
        }
    }

    // Erase all dead objects
    for(auto &i : deadList)
    {
        m_AliveList.erase(i);
        delete (*i);
    }
}

template<typename T>
void ObjectManager<T>::nextStep(void)
{
    for(auto &i: m_AliveList)
    {
        i->nextStep();
    }
}

template<typename T>
void ObjectManager<T>::draw(sf::RenderTarget &rt, sf::RenderStates s) const
{
    for(auto &i: m_AliveList)
    {
        rt.draw(*i, s);
    }
}
