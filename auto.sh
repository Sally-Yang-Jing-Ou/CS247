ssh -Y yjou@linux.student.cs.uwaterloo.ca 'mkdir -p cs247/project'
zip straights.zip -r *.cpp *.h in straights-sample Makefile
scp straights.zip yjou@linux.student.cs.uwaterloo.ca:/u1/yjou/cs247/project
ssh -Y yjou@linux.student.cs.uwaterloo.ca 'cd cs247/project; unzip -o straights.zip; chmod 777 straights-sample; g++ -std=c++0x *.cpp -o straights; diff <(./straights-sample 99 < in) <(./straights 99 < in)'

