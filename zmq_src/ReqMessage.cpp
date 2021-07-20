/*
  Copyright (C) 2018- SKALE Labs

  This file is part of sgxwallet.

  sgxwallet is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as published
  by the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  sgxwallet is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with sgxwallet. If not, see <https://www.gnu.org/licenses/>.

  @file ReqMessage.cpp
  @author Oleh Nikolaiev
  @date 2021
*/


#include "SGXWalletServer.hpp"

#include "ReqMessage.h"


Json::Value ECDSASignReqMessage::process() {
    auto base = getInt64Rapid("base");
    auto keyName = getStringRapid("keyName");
    auto hash = getStringRapid("messageHash");
    auto cert = getStringRapid("cert");
    if (!isKeyByOwner(keyName, cert)) {
        throw std::invalid_argument("Only owner of the key can access it");
    }
    auto result = SGXWalletServer::ecdsaSignMessageHashImpl(base, keyName, hash);
    result["type"] = ZMQMessage::ECDSA_SIGN_RSP;
    return result;
}

Json::Value BLSSignReqMessage::process() {
    auto keyName = getStringRapid("keyShareName");
    auto hash = getStringRapid("messageHash");
    auto t = getInt64Rapid("t");
    auto n = getInt64Rapid("n");
    auto cert = getStringRapid("cert");
    if (!isKeyByOwner(keyName, cert)) {
        throw std::invalid_argument("Only owner of the key can access it");
    }
    auto result = SGXWalletServer::blsSignMessageHashImpl(keyName, hash, t, n);
    result["type"] = ZMQMessage::BLS_SIGN_RSP;
    return result;
}

Json::Value importBLSReqMessage::process() {
    auto keyName = getStringRapid("keyShareName");
    auto keyShare = getStringRapid("keyShare");
    auto result = SGXWalletServer::importBLSKeyShareImpl(keyShare, keyName);
    if (result["status"] == 0) {
        auto cert = getStringRapid("cert");
        keysByOwners[keyName] = cert;
    }
    result["type"] = ZMQMessage::IMPORT_BLS_RSP;
    return result;
}

Json::Value importECDSAReqMessage::process() {
    auto keyName = getStringRapid("keyName");
    auto key = getStringRapid("key");
    auto result = SGXWalletServer::importECDSAKeyImpl(key, keyName);
    if (result["status"] == 0) {
        auto cert = getStringRapid("cert");
        keysByOwners[keyName] = cert;
    }
    result["type"] = ZMQMessage::IMPORT_ECDSA_RSP;
    return result;
}

Json::Value generateECDSAReqMessage::process() {
    auto result = SGXWalletServer::generateECDSAKeyImpl();
    string keyName = result["keyName"].asString();
    if (result["status"] == 0) {
        auto cert = getStringRapid("cert");
        keysByOwners[keyName] = cert;
    }
    result["type"] = ZMQMessage::GENERATE_ECDSA_RSP;
    return result;
}

Json::Value getPublicECDSAReqMessage::process() {
    auto keyName = getStringRapid("keyName");
    auto cert = getStringRapid("cert");
    if (!isKeyByOwner(keyName, cert)) {
        throw std::invalid_argument("Only owner of the key can access it");
    }
    auto result = SGXWalletServer::getPublicECDSAKeyImpl(keyName);
    result["type"] = ZMQMessage::GET_PUBLIC_ECDSA_RSP;
    return result;
}

Json::Value generateDKGPolyReqMessage::process() {
    auto polyName = getStringRapid("polyName");
    auto t = getInt64Rapid("t");
    auto result = SGXWalletServer::generateDKGPolyImpl(polyName, t);
    if (result["status"] == 0) {
        auto cert = getStringRapid("cert");
        keysByOwners[polyName] = cert;
    }
    result["type"] = ZMQMessage::GENERATE_DKG_POLY_RSP;
    return result;
}

Json::Value getVerificationVectorReqMessage::process() {
    auto polyName = getStringRapid("polyName");
    auto cert = getStringRapid("cert");
    if (!isKeyByOwner(polyName, cert)) {
        throw std::invalid_argument("Only owner of the key can access it");
    }
    auto t = getInt64Rapid("t");
    auto result = SGXWalletServer::getVerificationVectorImpl(polyName, t);
    result["type"] = ZMQMessage::GET_VV_RSP;
    return result;
}

Json::Value getSecretShareReqMessage::process() {
    auto polyName = getStringRapid("polyName");
    auto t = getInt64Rapid("t");
    auto n = getInt64Rapid("n");
    auto pubKeys = getJsonValueRapid("publicKeys");
    auto cert = getStringRapid("cert");
    if (!isKeyByOwner(polyName, cert)) {
        throw std::invalid_argument("Only owner of the key can access it");
    }
    auto result = SGXWalletServer::getSecretShareV2Impl(polyName, pubKeys, t, n);
    result["type"] = ZMQMessage::GET_SECRET_SHARE_RSP;
    return result;
}

Json::Value dkgVerificationReqMessage::process() {
    auto ethKeyName = getStringRapid("ethKeyName");
    auto t = getInt64Rapid("t");
    auto n = getInt64Rapid("n");
    auto idx = getInt64Rapid("index");
    auto pubShares = getStringRapid("publicShares");
    auto secretShare = getStringRapid("secretShare");
    auto cert = getStringRapid("cert");
    if (!isKeyByOwner(ethKeyName, cert)) {
        throw std::invalid_argument("Only owner of the key can access it");
    }
    auto result = SGXWalletServer::dkgVerificationV2Impl(pubShares, ethKeyName, secretShare, t, n, idx);
    result["type"] = ZMQMessage::DKG_VERIFY_RSP;
    return result;
}

Json::Value createBLSPrivateKeyReqMessage::process() {
    auto blsKeyName = getStringRapid("blsKeyName");
    auto ethKeyName = getStringRapid("ethKeyName");
    auto polyName = getStringRapid("polyName");
    auto secretShare = getStringRapid("secretShare");
    auto t = getInt64Rapid("t");
    auto n = getInt64Rapid("n");
    auto cert = getStringRapid("cert");
    if (!isKeyByOwner(ethKeyName, cert) || !isKeyByOwner(polyName, cert)) {
        throw std::invalid_argument("Only owner of the key can access it");
    }
    auto result = SGXWalletServer::createBLSPrivateKeyV2Impl(blsKeyName, ethKeyName, polyName, secretShare, t, n);
    if (result["status"] == 0) {
        keysByOwners[blsKeyName] = cert;
    }
    result["type"] = ZMQMessage::CREATE_BLS_PRIVATE_RSP;
    return result;
}

Json::Value getBLSPublicReqMessage::process() {
    auto blsKeyName = getStringRapid("blsKeyName");
    auto cert = getStringRapid("cert");
    if (!isKeyByOwner(blsKeyName, cert)) {
        throw std::invalid_argument("Only owner of the key can access it");
    }
    auto result = SGXWalletServer::getBLSPublicKeyShareImpl(blsKeyName);
    result["type"] = ZMQMessage::GET_BLS_PUBLIC_RSP;
    return result;
}

Json::Value getAllBLSPublicKeysReqMessage::process() {
    auto t = getInt64Rapid("t");
    auto n = getInt64Rapid("n");
    auto pubShares = getJsonValueRapid("publicShares");
    auto result = SGXWalletServer::calculateAllBLSPublicKeysImpl(pubShares, t, n);
    result["type"] = ZMQMessage::GET_ALL_BLS_PUBLIC_RSP;
    return result;
}

Json::Value complaintResponseReqMessage::process() {
    auto polyName = getStringRapid("polyName");
    auto t = getInt64Rapid("t");
    auto n = getInt64Rapid("n");
    auto idx = getInt64Rapid("ind");
    auto cert = getStringRapid("cert");
    if (!isKeyByOwner(polyName, cert)) {
        throw std::invalid_argument("Only owner of the key can access it");
    }
    auto result = SGXWalletServer::complaintResponseImpl(polyName, t, n, idx);
    result["type"] = ZMQMessage::COMPLAINT_RESPONSE_RSP;
    return result;
}

Json::Value multG2ReqMessage::process() {
    auto x = getStringRapid("x");
    auto result = SGXWalletServer::multG2Impl(x);
    result["type"] = ZMQMessage::MULT_G2_RSP;
    return result;
}

Json::Value isPolyExistsReqMessage::process() {
    auto polyName = getStringRapid("polyName");
    auto result = SGXWalletServer::isPolyExistsImpl(polyName);
    result["type"] = ZMQMessage::IS_POLY_EXISTS_RSP;
    return result;
}

Json::Value getServerStatusReqMessage::process() {
    auto result = SGXWalletServer::getServerStatusImpl();
    result["type"] = ZMQMessage::GET_SERVER_STATUS_RSP;
    return result;
}

Json::Value getServerVersionReqMessage::process() {
    auto result = SGXWalletServer::getServerVersionImpl();
    result["type"] = ZMQMessage::GET_SERVER_VERSION_RSP;
    return result;
}

Json::Value deleteBLSKeyReqMessage::process() {
    auto blsKeyName = getStringRapid("blsKeyName");
    auto cert = getStringRapid("cert");
    if (!isKeyByOwner(blsKeyName, cert)) {
        throw std::invalid_argument("Only owner of the key can access it");
    }
    auto result = SGXWalletServer::deleteBlsKeyImpl(blsKeyName);
    result["type"] = ZMQMessage::DELETE_BLS_KEY_RSP;
    return result;
}
