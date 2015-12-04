#include <unordered_set>
#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
#include <cstdlib>
#include <cmath>

using values_type = std::vector<int>;

struct DataSet
{
    const values_type origin_set;
    const int64_t origin_sum;

    DataSet(size_t count, int max_v, int min_v)
        : origin_set(make_set(count, max_v, min_v)),
          origin_sum(make_sum(origin_set))
    {

    }

    int64_t distance(const values_type &subset) const
    {
        int64_t sum = make_sum(subset);

        return std::abs(sum - origin_sum);
    }

    values_type make_subset() const
    {
        size_t count = size_t(std::rand()) % (origin_set.size());

        std::unordered_set<size_t> indexes;
        for (size_t i = 0; i < count; ++i) {
            size_t index = size_t(std::rand()) % origin_set.size();
            indexes.insert(index);
        }

        values_type v;
        for (auto i : indexes)
            v.push_back(origin_set[i]);
        return v;
    }

    static int64_t make_sum(const values_type &v)
    {
        int64_t sum = 0;
        for (auto i : v)
            sum += i;
        return sum;
    }
    static values_type make_set(const size_t count, int max_v = 1000, int min_v = -1000)
    {
        std::unordered_set<int> s;
        while (s.size() < count) {
            int n = std::rand() % max_v - min_v;
            s.insert(n);
        }

        values_type vals;
        for (int i : s)
            vals.push_back(i);
        return vals;
    }
};

double decrease_temperature(double t, size_t i)
{
    return t / double(i);
}

double get_transition_probality(double dE, double t)
{
    return std::exp(-dE/t);
}

bool is_transition(double p)
{
    double value = double(rand()) / double(RAND_MAX);
    return value <= p;
}

values_type generate_state_candidate(const DataSet &seq)
{
    return seq.make_subset();
}

int64_t calculate_energy(const DataSet &seq, const values_type &subset)
{
    return seq.distance(subset);
}

void print_set(const std::string &title, const values_type &values)
{
    std::cout << title << std::endl << "( ";
    for (auto j : values) {
        std::cout << j << " ";
    }
    std::cout << ")" << std::endl;
}

int main()
{
    std::srand(time(nullptr));
    DataSet data(100, 1000, -200);
    print_set("set", data.origin_set);

    double initial_temperature = 100000000.0;
    auto current_state = generate_state_candidate(data);
    double current_energy = calculate_energy(data, current_state);
    double t = initial_temperature;

    for (size_t i = 1; i < 10000000; i++) {
        auto state_candidate = generate_state_candidate(data);
        auto candidate_energy = calculate_energy(data, state_candidate);

        if (candidate_energy < current_energy) {
            current_energy = candidate_energy;
            current_state = state_candidate;
        } else {
            double p = get_transition_probality(candidate_energy - current_energy, t);
            if (is_transition(p)) {
                current_energy = candidate_energy;
                current_state = state_candidate;
            }
        }

        t = decrease_temperature(initial_temperature, i);

        if (candidate_energy < 1) {
            print_set("subset", current_state);
            break;
        }
    }
    return 0;
}

