FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc main.cpp -o program
RUN chmod +x program
