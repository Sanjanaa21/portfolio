import math

class KDNode:
    def __init__(self, point, sales_rep_id, left=None, right=None):
        self.point = point  # Tuple: (x, y)
        self.sales_rep_id = sales_rep_id
        self.left = left
        self.right = right

class KDTree:
    def __init__(self, points):
        self.root = self.build(points)

    def build(self, points, depth=0):
        if not points:
            return None

        k = len(points[0][0])  # Dimensions
        axis = depth % k
        points.sort(key=lambda x: x[0][axis])
        median = len(points) // 2

        return KDNode(
            point=points[median][0],
            sales_rep_id=points[median][1],
            left=self.build(points[:median], depth + 1),
            right=self.build(points[median + 1:], depth + 1)
        )

    def nearest_neighbor(self, root, target, depth=0, best=None):
        if root is None:
            return best

        k = len(target)
        axis = depth % k
        next_branch = None
        opposite_branch = None

        point_dist = self.distance(target, root.point)
        if best is None or point_dist < best[1]:
            best = (root.sales_rep_id, point_dist)

        if target[axis] < root.point[axis]:
            next_branch = root.left
            opposite_branch = root.right
        else:
            next_branch = root.right
            opposite_branch = root.left

        best = self.nearest_neighbor(next_branch, target, depth + 1, best)

        if abs(target[axis] - root.point[axis]) < best[1]:
            best = self.nearest_neighbor(opposite_branch, target, depth + 1, best)

        return best

    def distance(self, point1, point2):
        return math.sqrt(sum((a - b) ** 2 for a, b in zip(point1, point2)))

# Example Sales Rep Locations: [(x, y), id]
sales_reps = [
    ((2, 3), "Rep-A"),
    ((5, 4), "Rep-B"),
    ((9, 6), "Rep-C"),
    ((4, 7), "Rep-D"),
    ((8, 1), "Rep-E"),
    ((7, 2), "Rep-F")
]

# Build the KD-Tree
tree = KDTree(sales_reps)

# Query: New Customer Location
new_customer = (6, 3)

# Find Nearest Sales Rep
nearest_rep = tree.nearest_neighbor(tree.root, new_customer)
print(f"Nearest sales rep to customer at {new_customer}: {nearest_rep[0]} (Distance: {nearest_rep[1]:.2f})")
