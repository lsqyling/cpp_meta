//
// Created by 10580.
//

#ifndef CPP_META_SHORTEST_PATH_HPP
#define CPP_META_SHORTEST_PATH_HPP
#include <type_traits>
#include <utility>
#include "type_list.hpp"

namespace meta {
//define data structure types
template<typename Node>
concept Vertex = requires {
    Node::id;
};

template<Vertex F, Vertex T>
struct edge
{
    using from = F;
    using to = T;
};

template<typename Node = void>
requires (Vertex<Node> || std::is_void_v<Node>)
struct edge_trait
{
    template<typename E>
    using is_from = std::is_same<typename E::from, Node>;
    template<typename E>
    using is_to = std::is_same<typename E::to, Node>;
    template<typename E>
    using get_from = return_<typename E::from>;
    template<typename E>
    using get_to = return_<typename E::to>;
};

template<typename Link, TypeList Out = type_list<>>
struct chain;
template<Vertex F, TypeList Out>
struct chain<auto(*)(F)->void, Out>
{
    using from = F;
    using type = Out;
};

template<Vertex F, typename T, TypeList Out>
class chain<auto(*)(F)->T, Out>
{
    using to = typename chain<T,Out>::from;
public:
    using from = F;
    using type = typename chain<T, typename Out::template append<edge<from, to>>>::type;
};

template<typename Link>
using chain_t = typename chain<Link>::type;

#define node(node) auto(*)(node)
#define link(link) link->void

template<typename ...Chains>
struct graph
{
    using edges = unique_t<concat_t<chain_t<Chains>...>>;

    template<Vertex From, Vertex Target, TypeList Path>
    struct path_finder;

//    reach target
    template<Vertex Target, TypeList Path>
    struct path_finder<Target, Target, Path> : Path::template append<Target> {};

//    skip circle
    template<Vertex CurrNode, Vertex Target, TypeList Path>
    requires elem_v<Path, CurrNode>
    struct path_finder<CurrNode, Target, Path> : type_list<> {};
//    DFS
    template<Vertex CurrNode, Vertex Target, TypeList Path = type_list<>>
    class path_finder
    {
        using edges_from = filter_t<edges, edge_trait<CurrNode>::template is_from>;
        using next_nodes = map_t<edges_from, edge_trait<>::get_to>;

        template<Vertex AdjNode>
        using get_path = path_finder<AdjNode, Target, typename Path::template append<CurrNode>>;

        using all_path_from_curr_node = map_t<next_nodes, get_path>;
        template<TypeList AccMinPath, TypeList TmpPath>
        using get_min_path = std::conditional_t<AccMinPath::size == 0
                                                || (AccMinPath::size > TmpPath::size && TmpPath::size > 0),
                TmpPath, AccMinPath>;
    public:
        using type = fold_t<all_path_from_curr_node, type_list<>, get_min_path>;
    };

    template<Vertex From, Vertex Target>
    using path_finder_t = typename path_finder<From, Target>::type;

//    all shortest path
    template<TypeList A, TypeList B, template<typename, typename> class Pair>
    struct cross_product
    {
        template<TypeList ResOuter, typename ElemA>
        struct outer_append
        {
            template<TypeList ResInner, typename ElemB>
            using inner_append = typename ResInner::template append<Pair<ElemA, ElemB>>;
            using type = fold_t<B, ResOuter, inner_append>;

        };

        using type = fold_t<A, type_list<>, outer_append>;
    };
    template<TypeList A, TypeList B, template<typename, typename> class Pair>
            using cross_product_t = typename cross_product<A, B, Pair>::type;


    using all_node_pairs = cross_product_t<
            unique_t<map_t<edges, edge_trait<>::get_from>>,
            unique_t<map_t<edges, edge_trait<>::get_to>>,
            std::pair>;// type_list<std::pair<A,B>,..>

    template<typename NodePair>
    using is_non_empty_path = std::bool_constant<(path_finder_t<typename NodePair::first_type,
            typename NodePair::second_type>::size > 0)>;
    using reachable_node_pairs = filter_t<all_node_pairs, is_non_empty_path>;

//    path
    template<typename NodeType>
    struct path_ref
    {
        const NodeType *path;
        size_t sz;
    };

    template<Vertex Node, Vertex ...Nodes>
    class path_storage
    {
        using node_type = std::decay_t<decltype(Node::id)>;
        static constexpr node_type path_storage_[]{Node::id, Nodes::id...};

    public:
        static constexpr path_ref<node_type> path{
                .path = path_storage_,
                .sz = sizeof...(Nodes) + 1,
        };
    };

    template<typename NodePair>
    using save_path = return_<std::pair<NodePair,
                                        typename path_finder_t<typename NodePair::first_type,
                                                                typename NodePair::second_type>
                                                                ::template to<path_storage>>>;
    using save_all_path = map_t<reachable_node_pairs, save_path>;

    template<typename NodeType, Vertex From, Vertex Target, typename PathStorage>
    static constexpr bool match_path(NodeType from, NodeType to,
                                     path_ref<NodeType> &result,
                                     std::pair<std::pair<From, Target>, PathStorage>)
    {
        if (From::id == from && Target::id == to)
        {
            result = PathStorage::path;
            return true;
        }
        return false;
    }

    template<typename NodeType, typename ...PathPairs>
    static constexpr void match_path(NodeType from, NodeType to,
                                     path_ref<NodeType> &result,
                                     type_list<PathPairs...>)
    {
        (match_path(from, to, result, PathPairs{}) || ...);
    }

public:
    template<typename NodeType>
    static constexpr path_ref<NodeType> get_path(NodeType from, NodeType to)
    {
        path_ref<NodeType> result;
        match_path(from, to, result, save_all_path{});
        return result;
    }
};
}


#endif //CPP_META_SHORTEST_PATH_HPP
