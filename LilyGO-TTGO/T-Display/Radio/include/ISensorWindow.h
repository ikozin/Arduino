#pragma once

#include "ISensor.h"

template<typename DataType, size_t DataSize>
class ISensorWindow : public ISensor<DataType> {
    public: 
        ISensorWindow() {
            _length = DataSize;
        }
    protected:
        DataType    _data[DataSize];
        size_t      _length;
        int         _index;
    public:
        int Size() const { return _length; }
        DataType* GetWindow() const { return (DataType*)_data; }
    protected:
        void AddValue(DataType val) {
            if (_index < _length) {
                _data[_index++] = val;
            } else {
                size_t max = _length - 1;
                for (size_t i = 0; i < max; i++) {
                    _data[i] = _data[i + 1];
                }
                _data[max] = val;
            }
        }
};
