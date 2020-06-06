def best_value(offers, offer, cost_limit):
    if offer == 0:
        return 0
    elif offers[offer - 1][0] > cost_limit:
        return best_value(offers, offer - 1, cost_limit)
    else:
        return max(best_value(offers, offer - 1, cost_limit),
                   best_value(offers, offer - 1, cost_limit - offers[offer - 1][0]) + offers[offer - 1][1])


def backpack_solver(offers, cost_limit):
    result = []
    for i in reversed(range(len(offers))):
        if best_value(offers, i + 1, cost_limit) > best_value(offers, i, cost_limit):
            result.append(offers[i])
            cost_limit -= offers[i][0]
    return result
