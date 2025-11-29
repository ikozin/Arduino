#pragma once

#include "ISensor.h"
#include "IWindowFunction.h"

template<typename DataType, size_t DataSize, typename SliceFunc, size_t SliceSize>
class ISensorWindowFunc : public ISensor<DataType> {
    public: 
        ISensorWindowFunc() {
            _length = DataSize;
            _slice = SliceSize;
            _index = 0;
            _sliceIndex = _slice - 1;
            _func = new SliceFunc();
        }
    protected:
        DataType                    _data[DataSize];
        size_t                      _length;
        size_t                      _slice;
        size_t                      _index;
        size_t                      _sliceIndex;
        IWindowFunction<DataType>*  _func;
    public:
        size_t Size() const { return _length; }
        size_t Slice() const { return _slice; }
        DataType* GetWindow() const { return (DataType*)_data; }
    protected:
        void AddValue(DataType val) {
            LOG("Index=%d, Slice=%d, Val=%.1f, ", _index, _sliceIndex, val);
            _sliceIndex ++;
            if (_sliceIndex == _slice) {
                _func->Reset();
                val = _func->Calc(val);
                _sliceIndex = 0;
                _index++;
                if (_index == _length) {
                    size_t max = _length - 1;
                    for (size_t i = 0; i < max; i++) {
                        _data[i] = _data[i + 1];
                    }
                    _index = max;
                }
            }
            else {
                val = _func->Calc(val);
            }
            _data[_index] = val;
            LOGN("Index=%d, Slice=%d, Val=%.1f", _index, _sliceIndex, val);
        }
};
