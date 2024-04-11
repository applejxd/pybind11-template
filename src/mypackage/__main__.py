import numpy as np

from mypackage import bind


def main():
    bind.eigen.print_array(np.array([1, 2, 3]))


if __name__ == "__main__":
    main()
