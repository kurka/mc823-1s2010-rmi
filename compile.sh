javac -cp compute/Compute.java compute/Task.java
jar cvf compute.jar compute/*.class
cp compute.jar classes/compute.jar
cp mysql-connector-java-5.1.12-bin.jar classes/
mkdir classes/client
javac -cp classes/compute.jar engine/ComputeEngine.java
javac -cp classes/compute.jar client/ComputePi.java client/Pi.java
cp client/Pi.class classes/client
sudo cp -R classes /var/www/
