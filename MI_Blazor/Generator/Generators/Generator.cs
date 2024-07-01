using System;
using System.Collections.Generic;
using System.Text;
using Generator.Resources;

namespace Generator.Generators
{
    internal abstract class Generator<T>
    {
        protected readonly string _tableName;
        protected readonly string _valsStr;
        protected readonly string _insertStr;
        protected readonly string _filePath;
        protected readonly int _numberOfRecords;

        protected Generator(string tableName, string valsStr, string filePath, int numberOfRecords)
        {
            _tableName = tableName;
            _valsStr = valsStr;
            _insertStr = string.Format(SQLRes.InsertStatement, this._tableName, this._valsStr);
            _filePath = filePath;
            _numberOfRecords = numberOfRecords;
        }

        public abstract void Generate();

        public abstract List<string> CreateStringCollection(List<T> collection);
    }
}
