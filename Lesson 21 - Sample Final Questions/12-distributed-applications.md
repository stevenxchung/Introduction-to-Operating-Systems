# Problem 12: Distributed Applications

You are designing the new image datastore for an application that stores users' images (like [Picasa](http://picasa.google.com/)). The new design must consider the following scale:

- The current application has 30 million users
- Each user has on average 2,000 photos
- Each photo is on average 500 kB
- Requests are evenly distributed across all images

Answer the following:

1. Would you use replication or partitioning as a mechanism to ensure high responsiveness of the image store?
2. If you have 10 server machines at your disposal, and one of them crashes, what's the percentage of requests that the image store will not be able to respond to, if any?
