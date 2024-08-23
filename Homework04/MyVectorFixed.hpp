#ifndef CODEREVIEWTASK_MYVECTORFIXED_HPP
#define CODEREVIEWTASK_MYVECTORFIXED_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <memory>

template <typename T>
class MyVectorFixed
{
public:
    MyVectorFixed()
        : m_ref_ptr(std::make_shared<size_t>(1)),
        m_names(std::make_shared<std::vector<std::string>>())
    {
    }

    MyVectorFixed(const MyVectorFixed& other)
        : m_data(other.m_data),
        m_ref_ptr(other.m_ref_ptr),
        m_names(other.m_names)
    {
        (*m_ref_ptr)++;
    }

    ~MyVectorFixed()
    {
        if (--(*m_ref_ptr) == 0)
        {
            m_data.clear();
            m_names->clear();
        }
    }

    void push_back(const T& obj, const std::string& name)
    {
        copy_names();

        m_data.push_back(obj);
        m_names->push_back(name);
    }

    std::pair<const T&, const std::string&> operator[](int index) const
    {
        if (index < 0 || index >= m_data.size())
        {
            throw std::out_of_range("Index is out of range");
        }

        return std::pair<const T&, const std::string&>(m_data[index], (*m_names)[index]);
    }

    std::pair<T&, std::string&> operator[](int index)
    {
        if (index < 0 || index >= m_data.size())
        {
            throw std::out_of_range("Index is out of range");
        }

        return std::pair<T&, std::string&>(m_data[index], (*m_names)[index]);
    }

    const T& operator[](const std::string& name) const
    {
        auto iter = std::find(m_names->begin(), m_names->end(), name);
        if (iter == m_names->end())
        {
            throw std::invalid_argument(name + " is not found in the MyVectorFixed");
        }

        return m_data[iter - m_names->begin()];
    }

    T& operator[](const std::string& name)
    {
        auto iter = std::find(m_names->begin(), m_names->end(), name);
        if (iter == m_names->end())
        {
            throw std::invalid_argument(name + " is not found in the MyVectorFixed");
        }

        return m_data[iter - m_names->begin()];
    }

    // Additional functions
    auto begin() { return m_data.begin(); }
    auto cbegin() const { return m_data.cbegin(); }
    auto end() { return m_data.end(); }
    auto cend() const { return m_data.cend(); }
    bool empty() const { return m_data.empty(); }
    size_t size() const { return m_data.size(); }
    void reserve(size_t n) { m_data.reserve(n); }
    void clear() { m_data.clear(); m_names->clear(); }

private:
    void copy_names()
    {
        if (*m_ref_ptr == 1)
        {
            return;
        }

        m_ref_ptr = std::make_shared<size_t>(1);
        m_names = std::make_shared<std::vector<std::string>>(*m_names);
    }

private:
    std::vector<T> m_data;
    std::shared_ptr<size_t> m_ref_ptr;
    std::shared_ptr<std::vector<std::string>> m_names;
};

#endif // CODEREVIEWTASK_MYVECTORFIXED_HPP