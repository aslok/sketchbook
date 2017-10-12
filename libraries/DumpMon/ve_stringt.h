/**
 * @file ve_stringt.h
 * @brief String Header
 * @author andrey
 * @date 08.02.2012
 * @copyright GNU Public License
 */
#ifndef STRING_H_
#define STRING_H_

#include <stdlib.h>
#include <string.h>

/**
 * @addtogroup Strings
 * @{
 */

/**
 * @brief String class template
 */
template<typename _CharT, typename _IndexT>
class VeStringT
{
protected:
    _CharT *m_pData;					///< Pointer to character data
    _IndexT m_length;					///< Length of the data
protected:
    /**
     * @brief Reallocate string data
     * @param[in] _newLen New length value
     *
     * If length is zero, the data will be freed.
     */
    void realloc(_IndexT _newLen)
    {
        if (_newLen == 0)
        {
            free(m_pData);
            m_pData = 0;
            m_length = 0;
        }
        else if (_newLen != m_length)
        {
            size_t size = _newLen * sizeof(_CharT);
            _CharT *p = (_CharT*) malloc(size + 1);
            if (p == 0)
            	while(1) {}
            memcpy(p, m_pData, size);
            p[size] = 0;
            m_pData = p;
            m_length = _newLen;
        }
    }
public:
    /**
     * @brief Constructor
     */
    VeStringT() :
        m_pData(0), m_length(0)
    {
    }
    /**
     * @brief Destructor
     */
    ~VeStringT()
    {
        realloc(0);
    }
    /**
     * @brief Return true, if character is space character
     * @return True, if character is space character
     */
    static bool isSpace(const _CharT& _ch)
    {
        return (_ch < 33 || _ch == 127);
    }
    /**
     * @brief Return true, if the string is empty
     * @return True, if the string is empty
     */
    bool isEmpty() const
    {
        return m_length == 0;
    }
    /**
     * @brief Add character to the string
     * @param[in] _ch Character to add
     * @return Reference to this VeStringT
     */
    VeStringT& operator +=(const _CharT& _ch)
    {
        realloc(m_length + 1);
        m_pData[m_length - 1] = _ch;
        return (*this);
    }
    /**
     * @brief Return true, if string is equal to another string
     * @return True, if string is equal to another string
     */
    bool operator ==(const _CharT* _str) const
    {
        if (m_length == 0)
            return (_str[0] == 0);
        for (_IndexT n = 0; n < m_length; ++n)
        {
            if (_str[n] == 0)
                return false;
            if (_str[n] != m_pData[n])
                return false;
        }
        return _str[m_length] == 0;
    }
    /**
     * @brief Return the character by its index
     * @param[in] _n Index
     * @return Character
     */
    _CharT operator [](_IndexT _n) const
    {
        return m_pData[_n];
    }
};

typedef VeStringT<char, uint8_t> VeString;		///< 8-bit ANSI string class
/**
 * @}
 */
#endif /* STRING_H_ */
