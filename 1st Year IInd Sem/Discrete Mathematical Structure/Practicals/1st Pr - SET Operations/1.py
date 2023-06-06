# 1. Create a class SET. Create member functions to perform the following SET operations:
# 1) ismember: check whether an element belongs to the set or not and return value as true/false.
# 2) powerset: list all the elements of the power set of a set.
# 3) subset: Check whether one set is a subset of the other or not.
# 4) union and Intersection of two Sets.
# 5) complement: Assume Universal Set as per the input elements from the user.
# 6) set Difference and Symmetric Difference between two sets.
# 7) cartesian Product of Sets.
# Write a menu driven program to perform the above functions on an instance of the SET class.


class SET:
    # initiallising the class SET
    def __init__(self, elements):
        self.elements = elements
    
    # defining the ismember method to check whether an element is member or not.
    def ismember(self, element):
        return element in self.elements
    
    # defining the powerset method to write the poweset.
    def powerset(self):
        # as phi is the subset of everyset so intially defining it
        power_set = [[]]
        for element in self.elements:
            subsets = []
            for subset in power_set:
                subsets.append(subset + [element])
            power_set += subsets
        return power_set
    
    # defining the subset method to check whether a subset is subset of other or not.
    def subset(self, other_set):
        return set(self.elements).issubset(other_set.elements)
    
    # defining the union method to find the union of two sets
    def union(self, other_set):
        return set(self.elements).union(other_set.elements)

    # defining the intersection method to find the intersection of two sets
    def intersection(self, other_set):
        return set(self.elements).intersection(other_set.elements)
   
    # defining the complement method to find the complement relative to universal set provided by user.
    def complement(self, universal_set):
        return set(universal_set.elements).difference(self.elements)

    # defining the difference method to find the difference of two sets
    def difference(self, other_set):
        return set(self.elements).difference(other_set.elements)

    # defining the symmetric_difference method to find the symmetric_difference of two sets
    def symmetric_difference(self, other_set):
        return set(self.elements).symmetric_difference(other_set.elements)
    
    # defining the cartesian_product method to find the cartesian product of two sets
    def cartesian_product(self, other_set):
        cartesian = []
        for element1 in self.elements:
            for element2 in other_set.elements:
                cartesian.append((element1, element2))
        return cartesian
    
def main():
    print('SET Operations Menu \n')
    print("1. Check membership")
    print("2. Power set")
    print("3. Check subset")
    print("4. Union")
    print("5. Intersection")
    print("6. Complement")
    print("7. Set difference")
    print("8. Symmetric difference")
    print("9. Cartesian product")

    choice = input('\nEnter your choice: ')
    print()
    # Taking input for two sets
    print('Type the elements separated by comma\n')
    set1 = SET(input('Enter elements for set 1: ').split(','))
    set2 = SET(input('Enter elements for set 2: ').split(','))

    # Print the elements of set1 and set2
    print("\nSET 1: {" + ', '.join(set1.elements) + "}")
    print("SET 2: {" + ', '.join(set2.elements) + "}")
    
    if choice == '1':
        element = input('Enter the element to check membership: ')
        print(f"Is {element} a member of set 1? {set1.ismember(element)}")
        print(f"Is {element} a member of set 2? {set2.ismember(element)}")

    elif choice == '2':
        print("Power set of set 1:", set1.powerset())
        print("Power set of set 2:", set2.powerset())
    
    elif choice == '3':
        print(f"Is set 1 a subset of set 2? {set1.subset(set2)}")
        print(f"Is set 2 a subset of set 1? {set2.subset(set1)}")

    elif choice == '4':
        print("Union of set 1 and set 2:", set1.union(set2))

    elif choice == '5':
        print("Intersection of set 1 and set 2:", set1.intersection(set2))

    elif choice == '6':
        universal_set = SET(input("Enter elements for the universal set (comma-separated): ").split(','))
        print("Complement of set 1:", set1.complement(universal_set))
        print("Complement of set 2:", set2.complement(universal_set))

    elif choice == '7':
        print("Difference of set 1 and set 2:", set1.difference(set2))
        print("Difference of set 2 and set 1:", set2.difference(set1))

    elif choice == '8':
        print("Symmetric difference of set 1 and set 2:", set1.symmetric_difference(set2))

    elif choice == '9':
        print("Cartesian product of set 1 and set 2:", set1.cartesian_product(set2))
    else:
        print("Invalid choice. Please select a valid choice from below menu")
        main()

if __name__ == '__main__':
    main()
