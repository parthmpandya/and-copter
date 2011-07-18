#pragma once

typedef struct {void *p; void *pEnd;} Iterator;
typedef struct {void *p; void *pEnd;} MutableIterator;

template <typename T>
class List
{
    struct ListItem
    {
        ListItem* Next;
        T Data;
        ListItem(const T& init)
            : Data(init)
        {}
    };

    struct ListHeader
    {
        int  Size;
        int  RefCount;
        ListItem* pFront;
        ListItem* pTail;

        ListHeader()
            : Size(0), RefCount(1), pFront(0), pTail(0)
        {
        }

        ListItem* Root() const
        {
            return (ListItem*)(void*)&pFront;
        }
    } *m_header;

    void CopyBeforeWrite()
    {
        if (m_header->RefCount == 1) return;
        List<T> list;
        for (ListItem* p = m_header->pFront; p != 0; p = p->Next)
        {
            ListItem* item = new ListItem(p->Data);
            item->Next = 0;
            if (m_header->pTail != 0) m_header->pTail->Next = item;
            m_header->pTail = item;
            if (m_header->pFront == 0) m_header->pFront = item;
            m_header->Size ++;
        }
        ListHeader* t = m_header;
        m_header = list.m_header;
        list.m_header = t;
    }

    void Release()
    {
        if (--m_header->RefCount == 0)
        {   
            ListItem* p = m_header->pFront;
            while (p != 0)
            {
                ListItem* p2 = p;
                p = p->Next;
                delete p2; 
            }
            delete m_header;
        }
    }

public:
    List()
        : m_header(new ListHeader)
    {
    }

    List(const List<T>& list)
        : m_header(list.m_header)
    {
        m_header->RefCount++;
    }

    List<T>& operator = (const List<T>& list)
    {
        Release();
        m_header = list.m_header;
        m_header->RefCount++;
    }

    void Clear()
    {
        List<T> empty;
        ListHeader* t = m_header;
        m_header = empty.m_header;
        empty.m_header = t;
    }

    inline bool IsEmpty() const 
    {
        return m_header->pFront == 0;
    }

    int GetSize() const
    {
        return m_header->Size;
    }

    void PushFront(const T& item)
    {
        ListItem* li = new ListItem(item);
        CopyBeforeWrite();
        li->Next = m_header->pFront;
        m_header->pFront = li;
        if (m_header->pTail == 0) m_header->pTail = li;
        m_header->Size ++;
    }

    void PushBack(const T& item)
    {
        ListItem* li = new ListItem(item);
        CopyBeforeWrite();
        li->Next = 0;
        if (m_header->pTail != 0) m_header->pTail->Next = li;
        m_header->pTail = li;
        if (m_header->pFront == 0) m_header->pFront = li;
        m_header->Size ++;
    }

    void Append(const T& item)
    {
        PushBack(item);
    }

    void PopFront()
    {
        ListItem* front = m_header->pFront;
        m_header->pFront = front->Next;
        if (m_header->pTail == front) m_header->pTail = 0;
        delete front;
        m_header->Size --;
    }

    const T& Front() const
    {
        return m_header->pFront->Data;
    }

    const T& Back() const
    {
        return m_header->pTail->Data;
    }

    void Revert()
    {
        if (m_header->Size <= 1) return;
        CopyBeforeWrite();
        m_header->pTail = m_header->pFront;
        ListItem* i = m_header->pFront;
        ListItem* prev = 0;
        ListItem* t;
        while (i != 0)
        {
            t = i->Next;
            i->Next = prev;
            prev = i;
            i = t;
        }
        m_header->pFront = prev;
    }

    operator Iterator() const
    {
        Iterator it;
        it.p = (void*)m_header->Root();
        it.pEnd = (void*)m_header->pTail;
        return it;
    }

    void Iterate(Iterator& it) const
    {
        it.p = (void*)m_header->Root();
        it.pEnd = (void*)m_header->pTail;
    }

    bool HasNext(const Iterator& it) const
    {
        return ((ListItem*)it.p)->Next != 0;
    }

    bool Next(Iterator& it) const
    {
        if (it.p == 0 || it.p == it.pEnd) return false;
        it.p = ((ListItem*)it.p)->Next;
        return true;
    }

    const T& operator[](const Iterator& it) const
    {
        ListItem* current  = ((ListItem*)it.p)->Next;
        return current->Data;
    }

    operator MutableIterator()
    {
        MutableIterator it;
        CopyBeforeWrite();
        it.p = (void*)m_header->Root();
        it.pEnd = (void*)m_header->pTail;
        return it;
    }

    void Iterate(MutableIterator& it)
    {
        CopyBeforeWrite();
        it.p = (void*)m_header->Root();
        it.pEnd = (void*)m_header->pTail;
    }

    bool HasNext(const MutableIterator& it) const
    {
        return ((ListItem*)it.p)->Next != 0;
    }

    bool Next(MutableIterator& it) const
    {
        if (it.p == 0 || it.p == it.pEnd) return false;
        it.p = ((ListItem*)it.p)->Next;
        return true;
    }

    T& operator[](const MutableIterator& it) const
    {
        ListItem* current  = ((ListItem*)it.p)->Next;
        return current->Data;
    }
    void Insert(const MutableIterator& place, const T& item)
    {
        ListItem* it = new ListItem(item);
        ListItem* p = (ListItem*)place.p;
        it->Next = p->Next;
        p->Next = it;
        m_header->Size ++;
        if (m_header->pTail == p) m_header->pTail = it;
    }

    void Erase(const MutableIterator& place)
    {
        ListItem* p = (ListItem*)place.p;
        ListItem* removed = p->Next;
        p->Next = removed->Next;
        if (removed == m_header->pTail) m_header->pTail = p;
        delete removed;
        m_header->Size --;
    }

    bool Remove(const T& item)
    {
        CopyBeforeWrite();
        bool removed = false;
        ListItem* p = m_header->Root();
        while (p->Next != 0)
        {
            ListItem* current = p->Next;
            if (current->Data == item)
            {
                p->Next = current->Next;
                if (current == m_header->pFront)
                    m_header->pFront = current->Next;
                delete current;
                m_header->Size --;
                removed = true;
            }
            else p = p->Next;
        }
        m_header->pTail = p;
        return removed;
    }

    bool Contains(const T& item) const
    {
        ListItem* p = m_header->pFront;
        while (p) 
        {
            if (p->Data == item) return true;
            p = p->Next;
        }
        return false;
    }

    int Replace(const T& item, const T& newvalue)
    {
        int count = 0;
        CopyBeforeWrite();
        ListItem* p = m_header->pFront;
        while(p) 
        {
            if (p->Data == item)
            {
                p->Data = newvalue;
                ++count;
            }
            p = p->Next;
        }
        return count;
    }

    ~List()
    {
        Release();
    }
};