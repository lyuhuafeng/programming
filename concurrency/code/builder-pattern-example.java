// builder pattern 例子
class Employee {
    private final String name;
    private final int age;
    private final String department;

    private Employee(String name, int age, String department) {
        this.name = name;
        this.age = age;
        this.department = department;
    }

    public String toString() {
        return name + ", " + age + ", " + department;
    }
    public static class Builder {
        private String name;
        private int age;
        private String department;

        public Builder setName(String name) {
            this.name = name;
            return this;
        }

        public Builder setAge(int age) {
            this.age = age;
            return this;
        }

        public Builder setDepartment(String department) {
            this.department = department;
            return this;
        }

        public Employee build() {
            return new Employee(name, age, department);
        }
    }

    public static void main(String[] args) {
        Employee.Builder emplBuilder = new Employee.Builder();
        Employee employee = emplBuilder
                .setName("igor")
                .setDepartment("dev")
                .build();
        System.out.println(employee);
    }
}
