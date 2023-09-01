# TestAssignmentProject
<h3>Design a small program in C++ that would implement support of 3D curves hierarchy.</h3>

<p>1. Support a few types of 3D geometric curves – circles, ellipses and 3D helixes. (Simplified
definitions are below). Each curve should be able to return a 3D point and a first derivative (3D
vector) per parameter t along the curve.</p>

<p>2. Populate a container (e.g. vector or list) of objects of these types created in random manner with
random parameters.</p>

<p>3. Print coordinates of points and derivatives of all curves in the container at t=PI/4.</p>

<p>4. Populate a second container that would contain only circles from the first container. Make sure the
second container shares (i.e. not clones) circles of the first one, e.g. via pointers.</p>

<p>5. Sort the second container in the ascending order of circles’ radii. That is, the first element has the
smallest radius, the last - the greatest.</p>

<p>6. Compute the total sum of radii of all curves in the second container.</p>
<h3>(*) Additional optional requirements:</h3>
<p>7. Split implementation into a library of curves (.dll or .so) and executable which uses API of this
library.</p>
<p>8. Implement computation of the total sum of radii using parallel computations (e.g. OpenMP or Intel
TBB library).</p>
