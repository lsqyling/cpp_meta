//
// Created by 10580.
//

#ifndef CPP_META_INCLUDE_METANN_POLICY_POLICY_OP_HPP
#define CPP_META_INCLUDE_METANN_POLICY_POLICY_OP_HPP
#include "metann/metann_ns.hpp"
#include "metann/facilities/metann_trait.hpp"
METANN_NS_BEGIN

namespace NSPolicySelect {
template<typename MajorClass, typename PolicyCont>
struct selector
{
    using type = MajorClass;
};
}

template<typename MajorClass, typename PolicyCont>
using policy_select_t = NSPolicySelect::selector<MajorClass, PolicyCont>::type;







METANN_NS_END
#endif //CPP_META_INCLUDE_METANN_POLICY_POLICY_OP_HPP
