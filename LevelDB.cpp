/*
    Copyright (C) 2019 SKALE Labs

    This file is part of skale-consensus.

    skale-consensus is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    skale-consensus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with skale-consensus.  If not, see <https://www.gnu.org/licenses/>.

    @file LevelDB.cpp
    @author Stan Kladko
    @date 2019
*/


#include <stdexcept>
#include <memory>
#include <string>


#include "leveldb/db.h"


#include "LevelDB.h"

using namespace leveldb;


static WriteOptions writeOptions;
static ReadOptions readOptions;


std::shared_ptr<std::string> LevelDB::readString(std::string &_key) {

    auto result = std::make_shared<std::string>();

    if (db == nullptr) {
        throw std::runtime_error("Null db");
    }

    auto status = db->Get(readOptions, _key, &*result);

    throwExceptionOnError(status);

    if (status.IsNotFound())
        return nullptr;

    return result;
}

void LevelDB::writeString(const std::string &_key, const std::string &_value) {

    auto status = db->Put(writeOptions, Slice(_key), Slice(_value));

    throwExceptionOnError(status);
}

void LevelDB::writeByteArray(const char *_key, size_t _keyLen, const char *value,
                             size_t _valueLen) {

    auto status = db->Put(writeOptions, Slice(_key, _keyLen), Slice(value, _valueLen));

    throwExceptionOnError(status);
}


void LevelDB::writeByteArray(std::string &_key, const char *value,
                             size_t _valueLen) {

    auto status = db->Put(writeOptions, Slice(_key), Slice(value, _valueLen));

    throwExceptionOnError(status);
}

void LevelDB::throwExceptionOnError(Status _status) {
    if (_status.IsNotFound())
        return;

    if (!_status.ok()) {
        throw std::runtime_error("Could not write to database:" + _status.ToString());
    }

}

uint64_t LevelDB::visitKeys(LevelDB::KeyVisitor *_visitor, uint64_t _maxKeysToVisit) {

    uint64_t readCounter = 0;

    leveldb::Iterator *it = db->NewIterator(readOptions);
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        _visitor->visitDBKey(it->key().data());
        readCounter++;
        if (readCounter >= _maxKeysToVisit) {
            break;
        }
    }

    delete it;

    return readCounter;
}

LevelDB::LevelDB(std::string &filename) {


    leveldb::Options options;
    options.create_if_missing = true;

    if (!leveldb::DB::Open(options, filename, (leveldb::DB **) &db).ok()) {
        throw std::runtime_error("Unable to open levelDB database");
    }

    if (db == nullptr) {
        throw std::runtime_error("Null levelDB object");
    }

}

LevelDB::~LevelDB() {
    if (db != nullptr)
        delete db;
}

