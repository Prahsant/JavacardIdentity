/*
 * Copyright 2019, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "android.hardware.identity-service-jcic"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include "IdentityCredentialStore.h"

#include "JCSecureHardwareProxy.h"

using ::android::sp;
using ::android::base::InitLogging;
using ::android::base::StderrLogger;

using ::aidl::android::hardware::identity::IdentityCredentialStore;
using ::android::hardware::identity::JCSecureHardwareProxyFactory;
using ::android::hardware::identity::SecureHardwareProxyFactory;

int main(int /*argc*/, char* argv[]) {
    //InitLogging(argv, StderrLogger);

    sp<SecureHardwareProxyFactory> hwProxyFactory = new JCSecureHardwareProxyFactory();

    ABinderProcess_setThreadPoolMaxThreadCount(0);
    std::shared_ptr<IdentityCredentialStore> store =
            ndk::SharedRefBase::make<IdentityCredentialStore>(hwProxyFactory);

    const std::string instance = std::string() + IdentityCredentialStore::descriptor + "/jcic";
    binder_status_t status = AServiceManager_addService(store->asBinder().get(), instance.c_str());
    CHECK(status == STATUS_OK);

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
