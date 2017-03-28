import subprocess


cmd = ["./bin/HillClimberFirstImprovement", "--size", "10", "--nbeval", "2"]
r = subprocess.Popen(cmd, stdout=subprocess.PIPE, stdin=subprocess.PIPE)

# Send first solution
r.stdin.write("0-0-0-1-1-0-1-0-1-1")

# Print response
out = r.stdout.read()
print out

