# Input the number of marks for the question
total_marks = int(input())

# Input the number of options for the question
total_options = int(input())

# Input the correct options as a comma-separated sequence
correct_options = set(map(int, input().split(',')))

# Input the student's selected options as a comma-separated sequence
student_options = set(map(int, input().split(',')))

# Calculate the marks for the student
student_score = 0.0  # Initialize student's score as a float

# Check if the student's options are correct and calculate the score
if student_options.issubset(correct_options):
    # Student's options are entirely correct
    correct_option_count = len(student_options)
    student_score = total_marks * (correct_option_count / len(correct_options))
else:
    student_score=0

# Print the student's score as a float value
print(student_score)
