javac -cp ./mysql-connector-java-5.1.12-bin.jar compute/Compute.java compute/Task.java
jar cvf compute.jar compute/*.class ./mysql-connector-java-5.1.12-bin.jar
cp compute.jar classes/compute.jar
mkdir classes/client
javac -cp ./mysql-connector-java-5.1.12-bin.jar:classes/compute.jar engine/ComputeEngine.java
javac -cp ./mysql-connector-java-5.1.12-bin.jar:classes/compute.jar client/ComputePi.java client/Pi.java
cp client/Pi.class classes/client
sudo cp -R classes /var/www/
