#include <iostream>
#include <vector>
#include <memory>

enum class SamplingType
{
    eType_A,
    eType_B,
    eType_C,
};

struct SamplingBaseData
{
    const SamplingType type;
    const int time;
    SamplingBaseData(const SamplingType input_type, const int input_time)
        : type ( input_type )
        , time ( input_time )
    {
    }
};

template <typename SamplingTypes>
struct SamplingData : public SamplingBaseData
{
    const SamplingTypes data;
    SamplingData (const SamplingType input_type, const int input_time, const SamplingTypes & input_data)
        : SamplingBaseData(input_type, input_time)
        , data ( input_data )
    {
    }
};

class SamplingBuffer
{
public:
    SamplingBuffer( const SamplingType input_type )
        : m_sampling_type(input_type)
    {
    }
    void Push_Data( SamplingBaseData & data )
    {
        m_buffer.push_back(data);
    }
    std::size_t GetBufferSize()
    {
        return m_buffer.size();
    }
    bool isSameType( SamplingType type )
    {
        return (m_sampling_type == type);
    }
private:
    std::vector<SamplingBaseData> m_buffer;
    const SamplingType m_sampling_type;
};

class SamplingBufferRegister
{
public:
    void Push_Buffer( std::unique_ptr<SamplingBuffer> buffer )
    {
        regist_buffers.push_back(buffer);
    }
    void Push_Data_To_Buffer ( SamplingBaseData & data )
    {
        for( const auto & buffer : regist_buffers )
        {
            if( true == buffer.get()->isSameType(data.type))
            {
                buffer.get()->Push_Data(data);
            }
        }
    }
private:
    std::vector<std::unique_ptr<SamplingBuffer> > regist_buffers;
};