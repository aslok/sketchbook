/**
 * @file ve_fifo.h
 * @brief FIFO Header
 * @author andrey
 * @date 22.01.2012
 * @copyright GNU Public License
 */
#ifndef FIFO_H_
#define FIFO_H_

/**
 * @addtogroup FIFO
 * @{
 */

/**
 * @brief FIFO class template
 */
template<typename _T, typename _IndexT>
class FIFO
{
public:
    /**
     * @brief FIFO index class
     */
    class Index
    {
    protected:
        volatile _IndexT m_value;	///< Index value
        _IndexT m_min;				///< Minimum index value
        _IndexT m_max;				///< Maximum index value
    public:
        /**
         * @brief Constructor
         * @param[in] _min Minimum index value
         * @param[in] _max Maximum index value
         */
        Index(const _IndexT& _min, const _IndexT& _max) :
            m_value(_min), m_min(_min), m_max(_max)
        {
        }
        /**
         * @brief Increment Index value
         * @param[in] _incr Increment
         * @return Reference to this Index
         */
        Index& operator +=(int _incr)
        {
            m_value += _incr;
            if (m_value >= m_max)
            	m_value = m_min;
            return (*this);
        }
        /**
         * @brief Compare Index value with another Index value
         * @param[in] cmp Index to compare with
         * @return True, if indices are not equal
         */
        bool operator !=(const Index& cmp) const
        {
            return (m_value != cmp.m_value);
        }
        /**
         * @brief Return Index value
         * @return Index value
         */
        operator _IndexT() const
        {
            return m_value;
        }
    };
protected:
    Index m_nRead;		///< Read Index
    Index m_nWrite;		///< Write Index
    _T *m_pData;		///< Pointer to FIFO data
public:
    /**
     * @brief Constructor
     * @param[in] _data Pointer to data
     * @param[in] _size FIFO size
     */
    FIFO(_T* _data, uint8_t _size) :
    	m_nRead(0, _size), m_nWrite(0, _size), m_pData(_data)
    {
    }
    /**
     * @brief Return true, if Read and Write indices are not equal
     * @return True, if Read and Write indices are not equal
     */
    bool gotNewData() const
    {
        return (m_nRead != m_nWrite);
    }
    /**
     * @brief Push an item to the FIFO
     * @param[in] _item Item to push
     * @return Reference to the FIFO
     */
    FIFO& push(const _T& _item)
    {
    	m_pData[m_nWrite] = _item;
    	m_nWrite += 1;
        return (*this);
    }
    /**
     * @brief Pop item from the FIFO
     * @return Popped item
     */
    _T pop()
    {
        _T ret = m_pData[m_nRead];
        m_nRead += 1;
        return ret;
    }
};

typedef FIFO<uint8_t, uint8_t> U8fifo;	///< 8-bit FIFO class
/**
 * @}
 */
#endif /* FIFO_H_ */
