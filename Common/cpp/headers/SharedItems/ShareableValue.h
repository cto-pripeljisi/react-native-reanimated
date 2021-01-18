#pragma once

#include "WorkletsCache.h"
#include "SharedParent.h"
#include "Logger.h"
#include "ValueWrapper.h"
#include "HostFunctionHandler.h"
#include <string>
#include <mutex>
#include <unordered_map>
#include <jsi/jsi.h>
#include <JSIStoreValueUser.h>

using namespace facebook;

namespace reanimated {

class ShareableValue: public std::enable_shared_from_this<ShareableValue>, public StoreUser {
friend WorkletsCache;
friend FrozenObject;
friend void extractMutables(jsi::Runtime &rt,
                            std::shared_ptr<ShareableValue> sv,
                            std::vector<std::shared_ptr<MutableValue>> &res);

private:
  NativeReanimatedModule *module;
  std::unique_ptr<ValueWrapper> valueContainer;
  
//  bool boolValue;
//  double numberValue;
//  std::string stringValue;
  std::shared_ptr<HostFunctionHandler> hostFunction;
  jsi::Runtime *hostRuntime;
  //std::shared_ptr<FrozenObject> frozenObject;
  std::shared_ptr<RemoteObjectInitializer> remoteObjectInitializer;
//  std::shared_ptr<RemoteObject> remoteObject;
//  std::vector<std::shared_ptr<ShareableValue>> frozenArray;

  std::unique_ptr<jsi::Value> hostValue;
  std::weak_ptr<jsi::Value> remoteValue;

  jsi::Value toJSValue(jsi::Runtime &rt);

  jsi::Object createHost(jsi::Runtime &rt, std::shared_ptr<jsi::HostObject> host);

  ShareableValue(NativeReanimatedModule *module, std::shared_ptr<Scheduler> s): StoreUser(s), module(module) {}
  void adapt(jsi::Runtime &rt, const jsi::Value &value, ValueType objectType);
  void adaptCache(jsi::Runtime &rt, const jsi::Value &value);
  bool containsHostFunction = false;

public:
  ValueType type = ValueType::UndefinedType;
  std::shared_ptr<MutableValue> mutableValue;
  static std::shared_ptr<ShareableValue> adapt(jsi::Runtime &rt, const jsi::Value &value, NativeReanimatedModule *module, ValueType objectType = ValueType::UndefinedType);
  jsi::Value getValue(jsi::Runtime &rt);

};

}
