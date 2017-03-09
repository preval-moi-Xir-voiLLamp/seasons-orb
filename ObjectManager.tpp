/*! \file ObjectManager.tpp
 */

/*! \brief Destructor of ObjectManager
 */
 template <typename T>
ObjectManager<T>::~ObjectManager(void)
{
    for(auto &i: m_AliveList)
    {
        delete i;
    }
}

/*! \brief Spawns a new object
 *
 * This function will be used to create an object and store it in the
 * ObjectManager
 *
 * \tparam U The type of the object to create. It shall be a subtype of T * \tparam Args The list of type of the parameters
 * \tparam Args The list of the type of the arguments
 *
 * \return A pointer to the created object
 */
template<typename T>
template<typename U, typename... Args>
U* ObjectManager<T>::add(
    Args&& ... args
    /*!< The list of the argument to give to the constructor of U*/)
{
    U *created = new U(args...);
    m_AliveList.push_front(created);
    return created;
}

/*! \brief Update all objects that were created by this ObjectManager
 *
 * It is to be noted that the function operates in two steps, first it updates
 * all objects, then it deletes the dead ones.
 * This is because first, we do not want to operate on memory and update at the
 * same time, as some objects might point to an indice that is wrong in some
 * functions and second because it is safer to have all the objects update in
 * the same environment, and not have them modify the environment to the other
 * \todo Further encourage two steps decomposition by having a pre-update
 * function?
 */
template<typename T>
void ObjectManager<T>::update(
        float dt
        /*!< Time elapsed since last call of update*/)
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

/*! \brief Draw all the objects that were created by this ObjectManager
 */
template<typename T>
void ObjectManager<T>::draw(sf::RenderTarget &rt, sf::RenderStates s) const
{
    for(auto &i: m_AliveList)
    {
        rt.draw(*i, s);
    }
}
