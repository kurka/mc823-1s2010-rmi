javac compute/Compute.java compute/Task.java
jar cvf compute.jar compute/*.class
cp compute.jar classes/compute.jar
mkdir classes/client
javac -cp classes/compute.jar engine/ComputeEngine.java
javac -cp classes/compute.jar client/ComputePi.java client/Pi.java
cp client/Pi.class classes/client

